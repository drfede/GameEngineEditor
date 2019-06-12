#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "AssetManager.h"
#include "TextureManager.h"

class AssetManager;

class Editor {
private:
  bool m_isRunning;
  SDL_Window *window;
public:
  int ticksLastFrame;
  bool IsRunning() const;
  Editor();
  ~Editor();
  static SDL_Renderer *renderer;
  static SDL_Event event;
  static AssetManager *assetManager;
  void Initialize(int width, int height);
  void ProcessInput();
  void Update();
  void Render();
  void Destroy();
  void loadFirstScreen();
  void loadSecondScreen();
  void loadMap(int w, int h);
};

#endif
