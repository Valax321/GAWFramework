#include "game_state_machine.h"
#include "gaw_internal.h"

#include <SDL.h>

typedef struct GameStateListNode
{
    struct GameStateListNode* next;
    const GameState* state;
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

    GameStateListNode* pushQueue = stm->pushQueue;
    while (pushQueue)
    {
        GameStateListNode* t = pushQueue;
        pushQueue = pushQueue->next;

        SDL_free(t);
    }

    GameStateListNode* popQueue = stm->popQueue;
    while (popQueue)
    {
        GameStateListNode* t = popQueue;
        popQueue = popQueue->next;

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

void GameStateMachine_UpdateQueuedStates(GameStateMachine* stm)
{
    GameStateListNode* popItem = stm->popQueue;
    while (popItem)
    {
        GameStateListNode* i = popItem;
        popItem = popItem->next;

        i->state->exit(i->ctx);
        SDL_free(i);
    }
    stm->popQueue = NULL;

    GameStateListNode* pushItem = stm->pushQueue;
    while (pushItem)
    {
        GameStateListNode* i = pushItem;
        GameStateListNode* next = i->next;

        i->ctx = i->state->init(NULL);

        GameStateListNode* top = stm->top;
        stm->top = i;
        i->next = top;
        pushItem = next;
    }
    stm->pushQueue = NULL;
}

void GameStateMachine_Push(GameStateMachine* stm, const GameState* state)
{
    GameStateListNode* pushQueue = stm->pushQueue;

    GameStateListNode* newNode = SDL_malloc(sizeof(GameStateListNode));
    *newNode = (GameStateListNode){0};

    newNode->state = state;

    if (pushQueue == NULL)
    {
        stm->pushQueue = newNode;
    }
    else
    {
        while (pushQueue)
        {
            if (!pushQueue->next)
            {
                pushQueue->next = newNode;
                break;
            }

            pushQueue = pushQueue->next;
        }
    }
}

void GameStateMachine_Change(GameStateMachine* stm, const GameState* state)
{
    GameStateMachine_Pop(stm);
    GameStateMachine_Push(stm, state);
}

void GameStateMachine_Pop(GameStateMachine* stm)
{
    if (stm->top == NULL)
        return;

    GameStateListNode* top = stm->top;
    stm->top = top->next;

    GameStateListNode* popQueue = stm->popQueue;
    if (popQueue == NULL)
    {
        stm->popQueue = top;
    }
    else
    {
        while (popQueue)
        {
            if (!popQueue->next)
            {
                popQueue->next = top;
                break;
            }

            popQueue = popQueue->next;
        }
    }
}