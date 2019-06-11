#include <iostream>
#include "./Editor.h"


Editor::Editor(){
  this->m_isRunning = false;
}

Editor::~Editor(){

}

bool Editor::IsRunning()const{
  return this->m_isRunning;
}

void Editor::Initialize(int width, int height){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr << "Error initializing SDL" << std::endl;
    return;
  }
  if (TTF_Init() != 0){
    std::cerr << "Error initializing SDL_TTF" << std::endl;
  }
  window = SDL_CreateWindow(
    NULL,   //TITLE
    SDL_WINDOWPOS_CENTERED, //X POSITION
    SDL_WINDOWPOS_CENTERED, //Y POSITION
    width,                  //WINDOW WIDTH
    height,                 //WINDOW HEIGHT
    SDL_WINDOW_BORDERLESS
  );
  if (!window){
    std::cerr << "Error with SDL creating window" << std::endl;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer){
    std::cerr << "Error creating renderer" << std::endl;
    return;
  }

  m_isRunning = true;
  return;
}

void Editor::ProcessInput(){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type){
    case SDL_QUIT: {
      m_isRunning = false;
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        m_isRunning = false;
        break;
      }
    }
    default: {break;}
  }
}

void Editor::Update(){

}

void Editor::Render(){
  SDL_SetRenderDrawColor(renderer,21,21,21,255);
  SDL_RenderClear(renderer);

  SDL_Rect rect {
    100,
    100,
    80,
    80
  };

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderPresent(renderer);

}

void Editor::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
