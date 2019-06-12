#include "./AssetManager.h"
#include "./TextureManager.h"
#include <iostream>


AssetManager::AssetManager(EntityManager* manager): manager(manager){

}

void AssetManager::ClearData(){
  fonts.clear();
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize){
  fonts.emplace(fontId,FontManager::LoadFont(filePath,fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId){
  return fonts[fontId];
}

void AssetManager::AddTexture(std::string textureId, const char* filePath){
  textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId){
  return textures[textureId];
}

void AssetManager::printMap(){
  for (auto elem: fonts){
    std::cout << elem.first << " " << elem.second << std::endl;
  }
}
