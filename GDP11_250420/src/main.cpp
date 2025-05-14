
/* Game Structure:
 * Player:
 * The player has 3 lives.
 * Player can select between Attack, Parry, and Defend.
 *
 * Enemy:
 * Enemies will have increasing difficulty and life.
 * Each enemy has their own health and might choose between the same three actions: Attack, Parry, and Defend
 *
 * Game Loop:
 * Each round, the player and the enemy select an action.
 * The game evaluates the result of the round based on the selected actions.
 * Player wins by surviving as long as possible in the dueling arena
 * Game gets harder as the player defeats more enemies (increase enemy difficulty).
 *
 * Game Mechanics:
 *
 * Attack vs. Attack: Clash (optional fun mechanic to make this interesting)
 * Attack vs. Parry: Counter-attack, the player takes 2 damage.
 * Attack vs. Defend: Player takes half damage.
 * The goal is to survive by choosing wisely against tougher enemies.
 *
 */

 /*
  * Character:
  * Health System
  * - Health Amount **
  * - IsAlive ?
  * - Take Damage
  * - Heal ?
  * - Attack Damage Value **
  * - Defense **
  *
  *
  *
  */
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "DGDef.h"
#include "Log.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"

#include "Dialogue.h"
#include "StartMenu.h"
#include "GameView.h"
#include "GameOverView.h"
#include "raylib.h"
#include "AnimationHandle.h"



Camera2D camera = {
	{ 0.f, 0.f },
	{ 0.f, 0.f },
	0.f,
	1.f
};


std::ostream& operator<<(std::ostream& out, const EAction& action)
{
	switch (action)
	{
	case ATTACK: out << "ATTACK"; return out;
	case PARRY: out << "PARRY"; return out;
	case DEFEND: out << "DEFEND"; return out;
	case NONE: out << "NONE";
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const BattleResult& br)
{
	out << "inst. " << br.instigator->GetName() << " | " << br.target->GetName() << " | a. " << br.action << ", r. " << br.result << ", d. " << br.damage;
	return out;
}


std::vector<Dialogue*> ResolveActions(EAction characterAction, int target, std::vector<EAction> enemyActions);
BattleResult ComputeResult(Character& instigator, EAction action1, Character& target, EAction action2);



int main()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TextFormat("%.0fx%.0f As God Intended", WINDOW_WIDTH, WINDOW_HEIGHT));
	SetTargetFPS(TARGET_FPS);

	GameState::GetRef().SetPhase(EViewContext::START_MENU);
	GameState::GetRef().PushView(new StartMenu());



	//Animation animation = Animation(SpriteID::KNIGHT_DEATH, { 800, WINDOW_HEIGHT / 2.f }, false);
	//AnimationHandle animHandle = GameState::GetRef().RegisterAnimation(&animation);



	while (!WindowShouldClose() && GameState::GetRef().IsRunning())
	{
		GameState::GetRef().UpdateViews();

		if (GameState::GetRef().PeekPlayerAction() != EAction::IDLE)
		{
			int target = 0;
			EAction PlayerAction = GameState::GetRef().ConsumePlayerAction();
			std::vector<EAction> EnemyActions = { GameState::GetRef().Enemies[0].ChooseAction() };
			std::vector<Dialogue*> DialogueSequence = ResolveActions(PlayerAction, target, EnemyActions);
			while (!DialogueSequence.empty())
			{
				GameState::GetRef().PushView(DialogueSequence.back());
				DialogueSequence.pop_back();
			}
		}
		if (!GameState::GetRef().MainPlayer.IsAlive() && GameState::GetRef().GetPhase() == EViewContext::GAME_OVER)
		{
			GameState::GetRef().MainPlayer.SetHealth(1);
			GameState::GetRef().ClearViews();
			GameState::GetRef().SetPhase(EViewContext::GAME_OVER);
			GameState::GetRef().PushView(new GameOverView());
		}

		BeginDrawing();
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);
			GameState::GetRef().DrawAnimations();
			EndMode2D();

			// This is where UI should draw (absolute positioning)
			GameState::GetRef().GUIDrawViews();
			DrawFPS(WINDOW_WIDTH - 90, 10);
		}
		EndDrawing();
	}
	CloseWindow();
	return EXIT_SUCCESS;
}

/* Player Perspective
 * Attack - Unicast
 * Parry  - Unicast
 * Defend - Broadcast
 */
std::vector<Dialogue*> ResolveActions(EAction playerAction, int target, std::vector<EAction> enemyActions)
{
	std::map<std::pair<EAction, EAction>, std::string> canned
	{
		{{DEFEND, NONE}, "%s takes a defensive stance"},
		{{PARRY, NONE}, "%s takes a parry stance"},
		{{ATTACK, ATTACK}, "%s attacks %s for %d damage"},
		{{DEFEND, ATTACK}, "%s defends against %s attack and takes %d damage" },
		{{PARRY, ATTACK}, "%s parries %s attack and deals %d damage"}
	};


	std::vector<Dialogue*> DialogueSequence;
	Player& player = GameState::GetRef().MainPlayer;
	target = std::max(std::min(target, MAX_ENEMIES-1), 0); // clamp, no oob

	// Show statuses first so following damage calculations make sense to player
	// player
	if (canned.find({ playerAction, NONE }) != canned.end())
	{
		DialogueSequence.push_back(
			new Dialogue(
				TextFormat(canned[{playerAction, NONE }].c_str(), player.GetName().c_str()), 
				[playerAction]()
				{
					switch (playerAction) {
						case DEFEND: GameState::GetRef().playerModel.SwapSprite(KNIGHT_DEFEND); break;
						case PARRY: GameState::GetRef().playerModel.SwapSprite(KNIGHT_PARRY);   break;
					}
				},
				[]()
				{

				},
				[]()
				{
					GameState::GetRef().playerModel.SwapSprite(KNIGHT_IDLE);
				}
			));
	}
	// enemies
	for (int i = 0; i < enemyActions.size(); ++i)
	{
		Enemy& enemy = GameState::GetRef().Enemies[i];
		if (enemy.IsAlive())
		{
			EAction enemyAction = enemyActions[i];
			if (canned.find({ enemyAction, NONE }) != canned.end())
			{
				DialogueSequence.push_back(
					new Dialogue(
						TextFormat(canned[{enemyAction, NONE }].c_str(), enemy.GetName().c_str()),
						[&enemy, enemyAction]()
						{
							GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), enemyAction));
						},
						[]()
						{
						},
						[&enemy]()
						{
							GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), IDLE));
						}
					));
			}
		}
	}

	// A little hacky, take a snapshot of pre-battle states
	Player trackPlayer = player;
	std::vector<Enemy> trackBattle;
	for (const Enemy& e : GameState::GetRef().Enemies)
	{
		trackBattle.push_back(e);
	}

	// Resolve battle outcomes
	// player
	if (canned.find({playerAction,  enemyActions[target]}) != canned.end())
	{
		BattleResult result = ComputeResult(player, playerAction, GameState::GetRef().Enemies[target], enemyActions[target]);
		trackBattle[target].SetHealth(trackBattle[target].GetHealth() - result.damage);
		EMobType enemyType = trackBattle[target].GetMobType();
		DialogueSequence.push_back(
			new Dialogue(
				TextFormat(canned[{ playerAction, enemyActions[target] }].c_str(), result.instigator->GetName().c_str(), result.target->GetName().c_str(), result.damage),
				[result,enemyType]()
				{
					switch (result.result)
					{
						case ATTACK: GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_ATTACK); GameState::GetRef().enemyModel.SwapSprite(Enemy::GetHurtSprite(enemyType));break;
						case PARRY:  GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_PARRY);  GameState::GetRef().enemyModel.SwapSprite(Enemy::GetHurtSprite(enemyType));break;
						case DEFEND: GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_DEFEND); GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemyType, ATTACK));break;
						default:     GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_IDLE);   break;
					}
				},
				[result]()
				{
					result.target->SetHealth(result.target->GetHealth() - result.damage);
				},
				[result,enemyType]()
				{
					GameState::GetRef().playerModel.SwapSprite(KNIGHT_IDLE);
					GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemyType, IDLE));
				}
			));
		if (!trackBattle[target].IsAlive())
		{
			EMobType enemyType = trackBattle[target].GetMobType();
			DialogueSequence.push_back(
				new Dialogue(
					result.target->GetName() + " was defeated!",
					[enemyType]()
					{
						GameState::GetRef().enemyModel.SwapSprite(Enemy::GetDeathSprite(enemyType));
					},
					[]()
					{
					},
					[]()
					{
					}
				));
		}
	}
	// enemies
	for (int i = 0; i < enemyActions.size(); ++i)
	{
		Enemy& enemy = GameState::GetRef().Enemies[i];
		if (trackBattle[i].IsAlive() && trackPlayer.IsAlive())
		{
			if (canned.find({ enemyActions[i], playerAction }) != canned.end())
			{
				BattleResult bresult = ComputeResult(enemy, enemyActions[i], player, playerAction);
				trackPlayer.SetHealth(trackPlayer.GetHealth() - bresult.damage);
				DialogueSequence.push_back(
					new Dialogue(
						TextFormat(canned[{enemyActions[i], playerAction }].c_str(), bresult.instigator->GetName().c_str(), bresult.target->GetName().c_str(), bresult.damage),
						[bresult, &enemy]()
						{
							switch (bresult.result)
							{
								case ATTACK: GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_HURT);   GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), ATTACK)); break;
								case DEFEND: GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_ATTACK); GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), DEFEND)); break;
								case PARRY:  GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_HURT);   GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), PARRY));  break;
							}
						},
						[bresult]()
						{
							bresult.target->SetHealth(bresult.target->GetHealth() - bresult.damage);
						},
						[&enemy]()
						{
							GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_IDLE);
							GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(enemy.GetMobType(), IDLE));
						}
					));
				if (!trackPlayer.IsAlive())
				{
					DialogueSequence.push_back(
						new Dialogue(
							bresult.target->GetName() + " was defeated!",
							[]()
							{
								GameState::GetRef().playerModel.SwapSprite(SpriteID::KNIGHT_DEATH, false);
							},
							[]()
							{
								GameState::GetRef().SetPhase(EViewContext::GAME_OVER);
								GameState::GetRef().playerModel.Unregister();
								GameState::GetRef().enemyModel.Unregister();
							},
							[]()
							{
							}
						));
					break;
				}
			}
		}
	}
	bool allEnemiesDefeated = true;
	for (int i = 0; i < trackBattle.size(); ++i)
	{
		if (trackBattle[i].IsAlive())
		{
			allEnemiesDefeated = false;
			break;
		}
	}
	if (allEnemiesDefeated)
	{
		DialogueSequence.push_back(new Dialogue("All enemies defeated!",
			[]()
			{
				GameState::GetRef().Enemies[0].IncreaseDifficulty(++GameState::GetRef().difficulty);
				GameState::GetRef().enemyModel.SwapSprite(Enemy::GetActionSprite(GameState::GetRef().Enemies[0].GetMobType(), IDLE));
			}
		));
	}

	return DialogueSequence;
}
// BattleResult::result, answers question what happens to instigator's action when target does blah
//     A  D  P  Tgt
//  A  X  1  1      X = Both sides succeed
//  D  0  0  0      1 = instigator disadvantage
//  P  0  0  0      0 = Nothing happens
// Ins
BattleResult ComputeResult(Character& instigator, EAction action1, Character& target, EAction action2)
{

	BattleResult res = {};
	res.instigator = &instigator;
	res.target = &target;
	res.damage = 0;
	res.action = action1;
	res.result = EAction::NONE;

	//Character* temp = nullptr;
	switch (action1)
	{
		case ATTACK:
			switch (action2)
			{
				case ATTACK:
					res.result = ATTACK;
					res.damage = res.instigator->GetAtkPower();
				break;
				case PARRY:
					//temp = res.instigator;
					//res.instigator = res.target;
					//res.target = temp;
					//temp = nullptr;
					res.result = NONE;
					res.damage = res.instigator->GetAtkPower() * 2;
				break;
				case DEFEND:
					res.result = DEFEND;
					res.damage = 0;
				break;
				case NONE:
					res.result = action1;
					res.damage = res.instigator->GetAtkPower();
				break;
			}
		break;
		case PARRY:
			switch (action2)
			{
				case ATTACK:
					// res.intigator = &instigator
					res.result = PARRY;
					res.damage = res.instigator->GetAtkPower() * 2;
				break;
				case PARRY:
					res.result = NONE;
					res.damage = 0;
				break;
				case DEFEND:
					res.result = NONE;
					res.damage = 0;
				break;
				case NONE:
					res.result = NONE;
					res.damage = 0;
				break;
			}
		break;
		case DEFEND:
			switch (action2)
			{
				case ATTACK:
					//temp = res.instigator;
					//res.instigator = res.target;
					//res.target = temp; // because instigator is on receiving end
					//temp = nullptr;
					res.result = DEFEND;
					res.damage = 0;
				break;
				case PARRY:
					res.result = NONE;
					res.damage = 0;
				break;
				case DEFEND:
					res.result = NONE;
					res.damage = 0;
				break;
				case NONE:
					res.result = NONE;
					res.damage = 0;
				break;
			}
		break;
	}
	return res;
}