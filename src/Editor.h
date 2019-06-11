#ifndef EDITOR_H
#define EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Editor {
private:
  bool m_isRunning;
  SDL_Window *window;
  SDL_Renderer *renderer;
public:
  bool IsRunning() const;
  Editor();
  ~Editor();
  void Initialize(int width, int height);
  void ProcessInput();
  void Update();
  void Render();
  void Destroy();

};

#endif
