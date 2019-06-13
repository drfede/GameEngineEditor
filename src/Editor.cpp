#include <iostream>
#include "./Editor.h"
#include "./AssetManager.h"
#include "./FontManager.h"
#include "./EntityManager.h"
#include "./Entity.h"
#include "./Component.h"
#include "./Components/TextLabelComponent.h"
#include "./Map.h"


EntityManager manager;
SDL_Event Editor::event;
SDL_Renderer* Editor::renderer;
Entity* widthEntity = NULL;
Entity* heightEntity = NULL;
std::string text = "";
bool isLoadScreen = false;
bool canWrite = true;
bool mapIsLoaded = false;
int w,h;
int scale = 1;
int tileSize = 32;
AssetManager* Editor::assetManager = new AssetManager(&manager);
Map* map;



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
  map = new Map("jungle-tiletexture",2,32);
  //map->LoadMap("./assets/tilemaps/jungle.map",25,20);
  manager.listAllEntities();
  m_isRunning = true;
  return;
}

void Editor::loadFirstScreen(){

  assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(),14);
  assetManager->AddFont("charriot-font-big", std::string("./assets/fonts/charriot.ttf").c_str(),20);
  assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
  Entity& text1 (manager.AddEntity("widthtesto"));
  Entity& text2 (manager.AddEntity("heighttesto"));

  Entity& tutorialText (manager.AddEntity("tutorialText"));
  tutorialText.AddComponent<TextLabelComponent>(300,10,"Game Engine Editor","charriot-font-big",WHITE_COLOR);
  tutorialText.AddComponent<TextLabelComponent>(315,60,"Choose the dimensions","charriot-font",WHITE_COLOR);
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

void Editor::loadMap(int w, int h){
  canWrite = false;
  map->CreateMap("./assets/tilemaps/newJungle.map",w,h);
  manager.GetEntityByName("tutorialText")->Destroy();
  manager.GetEntityByName("heighttesto")->Destroy();
  manager.GetEntityByName("widthtesto")->Destroy();
  map->LoadMap("./assets/tilemaps/newJungle.map",w,h);
  mapIsLoaded = true;
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
      break;
    }
    case SDL_TEXTINPUT: {
      if (canWrite){
        text += event.text.text;
        std::cout << text << std::endl;
        if (isLoadScreen){
          heightEntity->GetComponent<TextLabelComponent>()->SetLabelText(text);
        } else {
          widthEntity->GetComponent<TextLabelComponent>()->SetLabelText(text);
        }
      }
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      int mouseX,mouseY;
      SDL_GetMouseState(&mouseX,&mouseY);
      if (mapIsLoaded){
        mouseX = mouseX / 32 / 2;
        mouseY = mouseY / 32 / 2;
        std::cout << "X: " << mouseX << " Y: " << mouseY<< std::endl;
        map -> UpdateMap("./assets/tilemaps/newJungle.map",5,5,mouseX,mouseY,3,10);
        manager.ClearData();
        map -> LoadMap("./assets/tilemaps/newJungle.map",5,5);
      }
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        m_isRunning = false;
        break;
      }
      if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER){
        if (isLoadScreen){
          h = static_cast<int>(atoi(text.c_str()));
          loadMap(w,h);
        } else {
          w = static_cast<int>(atoi(text.c_str()));
        }
        loadSecondScreen();
        break;
      }
    }
    default: {break;}
  }
}

void Editor::Update(){
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  ticksLastFrame = SDL_GetTicks();
  manager.Update(deltaTime);

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
