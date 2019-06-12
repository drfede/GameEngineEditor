#include <iostream>
#include "./Editor.h"
#include "./AssetManager.h"
#include "./FontManager.h"
#include "./EntityManager.h"
#include "./Entity.h"
#include "./Component.h"
#include "./Components/TextLabelComponent.h"


EntityManager manager;
SDL_Event Editor::event;
SDL_Renderer* Editor::renderer;
Entity* widthEntity = NULL;
Entity* heightEntity = NULL;
std::string text = "";
bool isLoadScreen = false;
AssetManager* Editor::assetManager = new AssetManager();



Editor::Editor(){
  this->m_isRunning = false;
  SDL_StopTextInput();
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

  loadFirstScreen();
  m_isRunning = true;
  return;
}

void Editor::loadFirstScreen(){
  assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(),14);
  Entity& text1 (manager.AddEntity("widthtesto"));
  Entity& text2 (manager.AddEntity("heighttesto"));

  Entity& tutorialText (manager.AddEntity("tutorialText"));
  tutorialText.AddComponent<TextLabelComponent>(300,10,"Choose the dimensions","charriot-font",WHITE_COLOR);
  tutorialText.AddComponent<TextLabelComponent>(50,150,"Write the Width of the Map: ","charriot-font",WHITE_COLOR);
  widthEntity = manager.GetEntityByName("widthtesto");
  widthEntity->AddComponent<TextLabelComponent>(260,150,"","charriot-font",WHITE_COLOR);
  heightEntity = manager.GetEntityByName("heighttesto");
  heightEntity->AddComponent<TextLabelComponent>(260,180,"","charriot-font",WHITE_COLOR);
}

void Editor::loadSecondScreen(){
  isLoadScreen = true;
  text = "";
  manager.GetEntityByName("tutorialText")->AddComponent<TextLabelComponent>(50,180,"Write the Height of the Map: ","charriot-font",WHITE_COLOR);
  heightEntity = manager.GetEntityByName("heighttesto");
  heightEntity->AddComponent<TextLabelComponent>(260,180,"","charriot-font",WHITE_COLOR);

}

void Editor::ProcessInput(){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type){
    case SDL_QUIT: {
      m_isRunning = false;
      break;
    }
    case SDLK_F1: {
      SDL_StartTextInput();
      break;
    }
    case SDLK_TAB: {
      text += "\n";
      std::cout << "AKKAPO";
      break;
    }
    case SDL_TEXTINPUT: {
      text += event.text.text;
      std::cout << text << std::endl;
      if (isLoadScreen){
        heightEntity->GetComponent<TextLabelComponent>()->SetLabelText(text);
      } else {
        widthEntity->GetComponent<TextLabelComponent>()->SetLabelText(text);

      }
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        m_isRunning = false;
        break;
      }
      if (event.key.keysym.sym == SDLK_RETURN){
        int k = atoi(text.c_str());
        std::cout << "NUMERO: " << k << std::endl;
        loadSecondScreen();
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
  manager.Render();

  SDL_RenderPresent(renderer);

}

void Editor::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}
