
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
#include "Player.h"
#include "Enemy.h"
#include "Log.h"

#include "raylib.h"

#define TIMESTAMP std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())

const int MAX_ENEMIES = 1;
const int MAX_DIFFICULTY = 5;
const bool GOD_MODE = 1;

struct GameState
{
	int difficulty = 0;
	Enemy Enemy[MAX_ENEMIES]; // enemy[MAX_ENEMIES]
	Player MainPlayer;
};
static GameState G_game_state = {};


struct BattleResult
{
	Character* instigator;
	Character* target;
	Action action;
	int damage;
};



void ResolveActions(GameState& state, Action characterAction, int target, std::vector<Action> enemyActionn);
BattleResult ComputeResult(Character& instigator, Action action1, Character& target, Action action2);

int main()
{
	G_game_state.MainPlayer = Player(5, 2, 2, "Guy");
	G_game_state.Enemy[0] = Enemy(2, 1, 0, "Slime A");
	while (G_game_state.MainPlayer.IsAlive())
	{
		if (G_game_state.difficulty == MAX_DIFFICULTY)
		{
			
			std::cout << std::endl << "Game Over.\n\nyeah you win" << std::endl;
			break;
		}
		else
		{
			G_game_state.Enemy[0].IncreaseDifficulty(++G_game_state.difficulty);
			Log::Separator();
			Log::LogMessage(MLOG_DEFAULT, "A wild " + G_game_state.Enemy->GetName() + " has appeared!");
			Log::Separator();
		}
		
		while (G_game_state.Enemy[0].IsAlive())
		{
			
			Action PlayerAction = G_game_state.MainPlayer.ChooseAction();
			Action EnemyAction = G_game_state.Enemy[0].ChooseAction();
			std::cout << "Player: " << PlayerAction << std::endl;
			std::cout << "Enemy: " << EnemyAction << std::endl;
			ResolveActions(G_game_state, PlayerAction, 0, { EnemyAction });
			if (!G_game_state.MainPlayer.IsAlive())
			{
				Log::LogMessage(MLOG_ERROR, "\n" + G_game_state.MainPlayer.GetName() + " falls in battle\nGame Over.\n");
				return EXIT_SUCCESS;
			}
		}

		Log::LogMessage(MLOG_DEFAULT, "\n" + G_game_state.Enemy[0].GetName() + " was defeated!\n");
	}
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