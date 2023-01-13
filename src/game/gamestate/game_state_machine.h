#pragma once

/**
 * Function for state initialization.
 * @param args User-defined state argument data.
 * @return Pointer to an optional allocated state context object. If not needed, return NULL.
*/
typedef void* (*GameState_Init)(void* args);

/**
 * Function for state exit.
 * @param ctx The state context object created by the init function. Can be NULL.
*/
typedef void (*GameState_Exit)(void* ctx);

typedef void (*GameState_Tick)(void* ctx);
typedef void (*GameState_Frame)(void* ctx);

typedef struct GameState
{
    const char* stateName; // For debugging
    GameState_Init init;
    GameState_Exit exit;
    GameState_Tick tick;
    GameState_Frame frame;
} GameState;

typedef struct GameStateMachine GameStateMachine;

GameStateMachine* GameStateMachine_Create(void);
void GameStateMachine_Destroy(GameStateMachine* stm);

const GameState* GameStateMachine_GetCurrent(GameStateMachine* stm);

void GameStateMachine_UpdateQueuedStates(GameStateMachine* stm);
void GameStateMachine_CallTick(GameStateMachine* stm);
void GameStateMachine_CallFrame(GameStateMachine* stm);

void GameStateMachine_Push(GameStateMachine* stm, const GameState* state);
void GameStateMachine_Change(GameStateMachine* stm, const GameState* state);
void GameStateMachine_Pop(GameStateMachine* stm);