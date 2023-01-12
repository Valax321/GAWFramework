#include "game_state_machine.h"
#include "gaw_internal.h"

#include <SDL.h>

typedef struct GameStateListNode
{
    struct GameStateListNode* next;
    GameState* state;
    void* ctx;
} GameStateListNode;

typedef struct GameStateMachine 
{
    GameStateListNode* top;
    GameStateListNode* pushQueue;
    GameStateListNode* popQueue;
} GameStateMachine;

GameStateMachine* GameStateMachine_Create(void)
{
    GameStateMachine* stm = SDL_malloc(sizeof(GameStateMachine));
    *stm = (GameStateMachine){0};
    return stm;
}

void GameStateMachine_Destroy(GameStateMachine* stm)
{
    GameStateListNode* node = stm->top;
    while (node)
    {
        GameStateListNode* t = node;
        node = node->next;

        t->state->exit(t->ctx);
        SDL_free(t);
    }

    SDL_free(stm);
}

const GameState* GameStateMachine_GetCurrent(GameStateMachine* stm)
{
    if (stm->top == NULL)
        return NULL;

    return stm->top->state;
}

void GameStateMachine_CallTick(GameStateMachine* stm)
{
    if (stm->top == NULL)
        return;

    stm->top->state->tick(stm->top->ctx);
}

void GameStateMachine_CallFrame(GameStateMachine* stm)
{
    if (stm->top == NULL)
        return;

    stm->top->state->frame(stm->top->ctx);
}

void GameStateMachine_Push(GameStateMachine* stm, const GameState* state)
{

}

void GameStateMachine_Change(GameStateMachine* stm, const GameState* state)
{

}

void GameStateMachine_Pop(GameStateMachine* stm)
{

}