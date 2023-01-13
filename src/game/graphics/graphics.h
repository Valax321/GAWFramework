#pragma once

typedef struct GraphicsState GraphicsState;

void Graphics_SetAttributes(void);
void Graphics_Init(struct SDL_Window* window, GraphicsState** outGraphicsState);
void Graphics_Destroy(GraphicsState* state);
void Graphics_HandleResize(GraphicsState* state, union SDL_Event* ev);
void Graphics_Frame(GraphicsState* state, struct GameStateMachine* stateMachine);