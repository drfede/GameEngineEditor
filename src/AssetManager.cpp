#include "./AssetManager.h"
#include <iostream>


AssetManager::AssetManager(){

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

void AssetManager::printMap(){
  for (auto elem: fonts){
    std::cout << elem.first << " " << elem.second << std::endl;
  }
}
