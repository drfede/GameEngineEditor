#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../AssetManager.h"

class TileComponent: public Component {
public:
  SDL_Texture *texture;
  SDL_Rect sourceRectangle;
  SDL_Rect destinationRectangle;
  glm::vec2 position;

  TileComponent(int sourceRectX, int sourceRectY,
    int x, int y, int tileSize, int tileScale, std::string assetTextureId){

      texture = Editor::assetManager->GetTexture(assetTextureId);

      sourceRectangle.x = sourceRectX;
      sourceRectangle.y = sourceRectY;
      sourceRectangle.w = tileSize;
      sourceRectangle.h = tileSize;

      destinationRectangle.x = x;
      destinationRectangle.y = y;
      destinationRectangle.w = tileSize * tileScale;
      destinationRectangle.h = tileSize * tileScale;

      position.x = x;
      position.y = y;

    }
  ~TileComponent(){
    SDL_DestroyTexture(texture);
  }

  void Update(float deltaTime) override {


  }

  void Render() override {
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
  }

private:
};


#endif
