#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "./FontManager.h"


class AssetManager {
private:
  std::map<std::string, TTF_Font*> fonts;
public:
  AssetManager();
  ~AssetManager();
  void ClearData();
  void AddFont(std::string fontId, const char* filePath, int fontSize);
  TTF_Font* GetFont(std::string fontId);
  void printMap();

};

#endif
