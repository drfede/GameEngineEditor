#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Editor.h"


class TextLabelComponent: public Component {
private:
  SDL_Rect position;
  std::string text;
  std::string fontFamily;
  SDL_Color color;
  SDL_Texture* texture;
public:
  TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color){
    this->position.x = x;
    this->position.y = y;
    this->text = text;
    this->fontFamily = fontFamily;
    this->color = color;
    SetLabelText(text);
  }

  void SetLabelText(std::string text){
    SDL_Surface* surface = TTF_RenderText_Blended(Editor::assetManager->GetFont(fontFamily), text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(Editor::renderer,surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
  }

  void Render() override{
    FontManager::Draw(texture, position);
  }
};

#endif
