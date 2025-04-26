
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
#include <iostream>
#include <vector>
#include <chrono>
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Log.h"
#include "Menu.h"
#include "Hud.h"
#include "raylib.h"



struct BattleResult
{
	Character* instigator;
	Character* target;
	Action action;
	int damage;
};

static GameState g_gamecontext = {};
static Camera2D camera = { 0 };


void ResolveActions(GameState& state, Action characterAction, int target, std::vector<Action> enemyActionn);
BattleResult ComputeResult(Character& instigator, Action action1, Character& target, Action action2);



int main()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TextFormat("%.0fx%.0f As God Intended", WINDOW_WIDTH, WINDOW_HEIGHT));
	SetTargetFPS(60);

	g_gamecontext.phase = GAMEPHASE::START_MENU;
	g_gamecontext.ViewStack.push_back(new Menu(g_gamecontext));
	//g_gamecontext.phase = GAMEPHASE::GAME_RUNNING;
	//g_gamecontext.ViewStack.push_back(new Hud(g_gamecontext));
	g_gamecontext.Enemy[0].IncreaseDifficulty(g_gamecontext.difficulty);

	while (!WindowShouldClose() && g_gamecontext.phase != GAMEPHASE::EXIT)
	{
		// This is where UI should
			// Respond to user input 
			// sync updates with models
		g_gamecontext.UpdateViews();
		if (g_gamecontext.playerAction != Action::WAIT)
		{
			Action playerInput = g_gamecontext.ConsumePlayerAction();
			Action EnemyAction = g_gamecontext.Enemy[0].ChooseAction();
			ResolveActions(g_gamecontext, playerInput, 0, { EnemyAction });
			if (!g_gamecontext.Enemy[0].IsAlive())
			{
				g_gamecontext.Enemy[0].IncreaseDifficulty(++g_gamecontext.difficulty);
			}
		}
		BeginDrawing();
		{
			ClearBackground(BLACK);
			BeginMode2D(camera);
			// This is where viewport relative objects are drawn e.g. camera shake
			EndMode2D();
			// This is where UI should draw (absolute positioning)
			g_gamecontext.DrawViews();
			DrawFPS(WINDOW_WIDTH - 90, 10);
		}
		EndDrawing();

		if (!g_gamecontext.MainPlayer.IsAlive() || g_gamecontext.difficulty == MAX_DIFFICULTY)
		{
			g_gamecontext.phase = GAMEPHASE::GAME_OVER;
		}
	}
	CloseWindow();
	/*
	while (g_gamecontext.MainPlayer.IsAlive())
	{
		if (g_gamecontext.difficulty == MAX_DIFFICULTY)
		{
			std::cout << std::endl << "Game Over.\n\nyeah you win" << std::endl;
			break;
		}
		else
		{
			g_gamecontext.Enemy[0].IncreaseDifficulty(++g_gamecontext.difficulty);
			Log::Separator();
			Log::LogMessage(MLOG_DEFAULT, "A wild " + g_gamecontext.Enemy->GetName() + " has appeared!");
			Log::Separator();
		}

		while (g_gamecontext.Enemy[0].IsAlive())
		{
			Action PlayerAction = g_gamecontext.MainPlayer.ChooseAction();
			Action EnemyAction = g_gamecontext.Enemy[0].ChooseAction();
			std::cout << "Player: " << PlayerAction << std::endl;
			std::cout << "Enemy: " << EnemyAction << std::endl;
			ResolveActions(g_gamecontext, PlayerAction, 0, { EnemyAction });
			if (!g_gamecontext.MainPlayer.IsAlive())
			{
				Log::LogMessage(MLOG_ERROR, "\n" + g_gamecontext.MainPlayer.GetName() + " falls in battle\nGame Over.\n");
				return EXIT_SUCCESS;
			}
		}

		Log::LogMessage(MLOG_DEFAULT, "\n" + g_gamecontext.Enemy[0].GetName() + " was defeated!\n");
	}
	*/
	return EXIT_SUCCESS;
}

/* Player Perspective
 * Attack - Unicast
 * Parry  - Unicast
 * Defend - Broadcast
 */
void ResolveActions(GameState& state, Action characterAction, int target, std::vector<Action> enemyAction)
{
	target = std::max(std::min(target, MAX_ENEMIES), 0);

	std::vector<LogEntry> lmsg = std::vector<LogEntry>();
	BattleResult outcome;
	if (characterAction == DEFEND)
	{
		lmsg.push_back({ MLOG_DEFAULT, state.MainPlayer.GetName() + " switches to a defensive stance.", TIMESTAMP });
	}
	else if (characterAction == PARRY)
	{
		lmsg.push_back({ MLOG_DEFAULT, state.MainPlayer.GetName() + " switches to a parry stance.", TIMESTAMP });
	}
	else if (characterAction == ATTACK)
	{
		if (enemyAction[target] == ATTACK)
		{
			outcome = ComputeResult(state.MainPlayer, ATTACK, state.Enemy[target], ATTACK);
			outcome.target->SetHealth(outcome.target->GetHealth() - outcome.damage);
			lmsg.push_back({ MLOG_INFO, outcome.instigator->GetName() + " attacks " + outcome.target->GetName() + " for " + std::to_string(outcome.damage) + " damage (" + std::to_string(outcome.target->GetHealth()) + "/" + std::to_string(outcome.target->GetMaxHealth()) + ")", TIMESTAMP});
		}
	}

	Action characterTargetAction;
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (!state.Enemy[i].IsAlive())
		{
			continue;
		}
		if (characterAction != DEFEND && i != target)
		{
			characterTargetAction = NONE;
		}
		else
		{
			characterTargetAction = characterAction;
		}
		outcome = ComputeResult(state.Enemy[i], enemyAction[i], state.MainPlayer, characterTargetAction);
		if (!GOD_MODE || (GOD_MODE && outcome.target->GetName() != state.MainPlayer.GetName()))
		{
			outcome.target->SetHealth(outcome.target->GetHealth() - outcome.damage);
		}
		if (outcome.action == DEFEND) lmsg.push_back({ MLOG_WARNING, outcome.target->GetName() + " defends against " + outcome.instigator->GetName() + "'s attack and takes " + std::to_string(outcome.damage) + " damage (" + std::to_string(outcome.target->GetHealth()) + "/" + std::to_string(outcome.target->GetMaxHealth()) + ")", TIMESTAMP });
		if (outcome.action == PARRY) lmsg.push_back({ (outcome.target->GetName() != state.MainPlayer.GetName() ? MLOG_INFO : MLOG_ERROR), outcome.target->GetName() + "'s attack was parried by " + outcome.instigator->GetName() + "! " + outcome.target->GetName() + " takes " + std::to_string(outcome.damage) + " damage (" + std::to_string(outcome.target->GetHealth()) + "/" + std::to_string(outcome.target->GetMaxHealth()) + ")", TIMESTAMP });
		if (outcome.action == ATTACK) lmsg.push_back({ MLOG_ERROR, outcome.instigator->GetName() + " attacks " + outcome.target->GetName() + " for " + std::to_string(outcome.damage) + " damage (" + std::to_string(outcome.target->GetHealth()) + "/" + std::to_string(outcome.target->GetMaxHealth()) + ")", TIMESTAMP });
		if (outcome.action == NONE)
		{
			if (enemyAction[i] == DEFEND) lmsg.push_back({ MLOG_DEFAULT, state.Enemy[i].GetName() + " defends. Nothing happens", TIMESTAMP });
			if (enemyAction[i] == PARRY) lmsg.push_back({ MLOG_DEFAULT, state.Enemy[i].GetName() + " parries. Nothing happens", TIMESTAMP });
		}
	}

	for (auto lm : lmsg)
	{
		Log::PrintLog(lm);
	}
}
// Answers question what happens to instigator's action when target does blah
BattleResult ComputeResult(Character& instigator, Action action1, Character& target, Action action2)
{
	
	BattleResult res = {};
	res.instigator = &instigator;
	res.target = &target;
	res.damage = 0;

	Character* temp = nullptr;
	switch (action1)
	{
		case ATTACK:
			switch (action2)
			{
				case ATTACK:
					res.action = ATTACK;
					res.damage = res.instigator->GetAtkPower();
				break;
				case PARRY:
					temp = res.instigator;
					res.instigator = res.target;
					res.target = temp;
					temp = nullptr;
					res.action = PARRY;
					res.damage = res.instigator->GetAtkPower() * 2;
				break;
				case DEFEND:
					res.action = DEFEND;
					res.damage = 0;
				break;
				case NONE:
					res.action = action1;
					res.damage = res.instigator->GetAtkPower();
				break;
			}
		break;
		case PARRY:
			switch (action2)
			{
				case ATTACK:
					res.action = PARRY;
					res.damage = res.instigator->GetAtkPower() * 2;
				break;
				case PARRY:
					res.action = NONE;
					res.damage = 0;
				break;
				case DEFEND:
					res.action = NONE;
					res.damage = 0;
				break;
				case NONE:
					res.action = NONE;
					res.damage = 0;
				break;
			}
		break;
		case DEFEND:
			switch (action2)
			{
				case ATTACK:
					temp = res.instigator;
					res.instigator = res.target;
					res.target = temp; // because instigator is on receiving end
					temp = nullptr;
					res.action = DEFEND;
					res.damage = 0;
				break;
				case PARRY:
					res.action = NONE;
					res.damage = 0;
				break;
				case DEFEND:
					res.action = NONE;
					res.damage = 0;
				break;
				case NONE:
					res.action = NONE;
					res.damage = 0;
				break;
			}
		break;
	}
	return res;
}