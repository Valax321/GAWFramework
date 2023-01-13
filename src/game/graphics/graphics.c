#include "graphics.h"
#include "gamestate/game_state_machine.h"
#include "gaw_internal.h"

#include "raymath.h"
#include "rlgl.h"

#include <SDL.h>
#include <stdio.h>

#define RENDER_WIDTH 400
#define RENDER_HEIGHT 300

typedef struct Framebuffer
{
    uint32_t fbo;
    uint32_t texture;
    uint32_t depth;
} Framebuffer;

typedef struct GraphicsState
{
    void* glContext;
    SDL_Window* window;
    Framebuffer gameTarget;
} GraphicsState;

void Graphics_SetAttributes(void)
{
    #if defined(GAME_BUILD_FOR_DESKTOP)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    #endif
}

void Graphics_Init(SDL_Window* window, GraphicsState** outGraphicsState)
{
    GraphicsState* state = SDL_malloc(sizeof(GraphicsState));
    *state = (GraphicsState){0};

    state->window = window;
    state->glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    rlLoadExtensions(&SDL_GL_GetProcAddress);

    // Creates the framebuffer
    {
        state->gameTarget.fbo = rlLoadFramebuffer(RENDER_WIDTH, RENDER_HEIGHT);
        if (state->gameTarget.fbo > 0)
        {
            rlEnableFramebuffer(state->gameTarget.fbo);

            state->gameTarget.texture = rlLoadTexture(NULL, RENDER_WIDTH, RENDER_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
            state->gameTarget.depth = rlLoadTextureDepth(RENDER_WIDTH, RENDER_HEIGHT, true);

            rlFramebufferAttach(state->gameTarget.fbo, state->gameTarget.texture, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
            rlFramebufferAttach(state->gameTarget.fbo, state->gameTarget.depth, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
            rlFramebufferComplete(state->gameTarget.fbo);
            printf("Created rendering framebuffer");
            
            rlDisableFramebuffer(state->gameTarget.fbo);
        }
    }

    int w, h;
    SDL_GL_GetDrawableSize(g_GameState.window, &w, &h);
    rlglInit(w, h);
    rlViewport(0, 0, w, h);

    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, w, h, 0, 0.0f, 1.0f);
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    rlClearColor(0, 0, 0, 255);
    rlEnableDepthTest();

    *outGraphicsState = state;
}

void Graphics_Destroy(GraphicsState* state)
{
    rlUnloadFramebuffer(state->gameTarget.fbo);

    SDL_GL_DeleteContext(state->glContext);
    SDL_free(state);
}

void Graphics_HandleResize(GraphicsState* state, SDL_Event* ev)
{
    switch (ev->type)
    {
        case SDL_WINDOWEVENT:
        {
            if (ev->window.event == SDL_WINDOWEVENT_RESIZED)
            {
                printf("Window resized to %dx%d\n", ev->window.data1, ev->window.data2);
                int w, h;
                SDL_GL_GetDrawableSize(state->window, &w, &h);
                rlSetFramebufferWidth(w);
                rlSetFramebufferHeight(h);
            }
        }
        break;
    }
}

void Graphics_Frame(GraphicsState* state, struct GameStateMachine* stateMachine)
{
    // Clear the backbuffer
    rlClearScreenBuffers();

    // Draw the game view
    {
        rlEnableFramebuffer(state->gameTarget.fbo);
        rlViewport(0, 0, RENDER_WIDTH, RENDER_HEIGHT);
        rlSetFramebufferWidth(RENDER_WIDTH);
        rlSetFramebufferHeight(RENDER_HEIGHT);

        rlMatrixMode(RL_PROJECTION);
        rlLoadIdentity();

        rlOrtho(0, RENDER_WIDTH, RENDER_HEIGHT, 0, 0.0f, 1.0f);

        rlMatrixMode(RL_MODELVIEW);
        rlLoadIdentity();

        if (stateMachine)
            GameStateMachine_CallFrame(stateMachine);

        rlDrawRenderBatchActive();
        rlDisableFramebuffer();
    }

    {
        int w, h;
        SDL_GL_GetDrawableSize(state->window, &w, &h);
        rlViewport(0, 0, w, h);

        rlMatrixMode(RL_PROJECTION);
        rlLoadIdentity();

        rlOrtho(0, w, h, 0, 0.0f, 1.0f);

        rlMatrixMode(RL_MODELVIEW);
        rlLoadIdentity();

        SDL_FRect sourceRect = { 0.0f, 0.0f, (float)RENDER_WIDTH, (float)RENDER_HEIGHT };
        float virtualRatio = sourceRect.w / sourceRect.h;

        SDL_FRect destRect = { -virtualRatio, -virtualRatio, w + (virtualRatio * 2), h + (virtualRatio * 2) };

        // https://github.com/raysan5/raylib/blob/master/src/rtextures.c#L3550
        {
            rlSetTexture(state->gameTarget.texture);
            rlBegin(RL_QUADS);
                rlColor4ub(255, 255, 255, 255);
                rlNormal3f(0, 0, 1);
                /*
                if (flipX) rlTexCoord2f((source.x + source.width)/width, source.y/height);
                else rlTexCoord2f(source.x/width, source.y/height);
                rlVertex2f(topLeft.x, topLeft.y);

                // Bottom-left corner for texture and quad
                if (flipX) rlTexCoord2f((source.x + source.width)/width, (source.y + source.height)/height);
                else rlTexCoord2f(source.x/width, (source.y + source.height)/height);
                rlVertex2f(bottomLeft.x, bottomLeft.y);

                // Bottom-right corner for texture and quad
                if (flipX) rlTexCoord2f(source.x/width, (source.y + source.height)/height);
                else rlTexCoord2f((source.x + source.width)/width, (source.y + source.height)/height);
                rlVertex2f(bottomRight.x, bottomRight.y);

                // Top-right corner for texture and quad
                if (flipX) rlTexCoord2f(source.x/width, source.y/height);
                else rlTexCoord2f((source.x + source.width)/width, source.y/height);
                rlVertex2f(topRight.x, topRight.y);
                */
            rlEnd();
            rlSetTexture(0);
        }

        rlDrawRenderBatchActive();
    }

    SDL_GL_SwapWindow(state->window);
}