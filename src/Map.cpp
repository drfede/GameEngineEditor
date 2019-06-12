#include "./Editor.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"
#include <fstream>
#include <iostream>

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize){
  this -> textureId = textureId;
  this -> scale = scale;
  this -> tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY){
  // read the map tile definitions from .map files
  std::fstream mapFile;
  mapFile.open(filePath);

  for (int y = 0; y < mapSizeY; y++){
    for (int x = 0; x < mapSizeX; x++){
      char ch;
      mapFile.get(ch);
      int sourceRectY = atoi(&ch) * tileSize;
      mapFile.get(ch);
      int sourceRectX = atoi(&ch) * tileSize;
      AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
      mapFile.ignore(); //there's a comma to avoid
    }
  }
}

void Map::UpdateMap(std::string filePath, int mapSizeX, int mapSizeY, int toChangeX, int toChangeY){
  std::fstream mapFile;
  mapFile.open(filePath);

  for (int y = 0; y < mapSizeY; y++){
    for (int x = 0; x < mapSizeX; x++){
      char ch;
      if (x == toChangeX-1 && y == toChangeY-1){
        int newX = mapFile.peek();
        mapFile << static_cast<char>(newX+1);
        int newY = mapFile.peek();
        mapFile << static_cast<char>(newY+1);
        std::cout << "LAX: " << static_cast<char>(newX) << " LAY: " << static_cast<char>(newY) <<std::endl;
      }
      mapFile.get(ch);
      int sourceRectY = atoi(&ch) * tileSize;
      mapFile.get(ch);
      int sourceRectX = atoi(&ch) * tileSize;
      AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
      mapFile.ignore(); //there's a comma to avoid
    }
  }
}

void Map::CreateMap(std::string filePath, int mapSizeX, int mapSizeY){
  std::fstream mapFile;
  mapFile.open(filePath, std::ofstream::out);

  for (int y = 0; y <mapSizeY; y++){
    for (int x = 0; x < mapSizeX; x++){
      if (x == mapSizeX-1)
        mapFile << "0" << "0";
      else
        mapFile << "0" << "0" << ",";
    }
    mapFile << std::endl;
  }
  mapFile << std::endl;
  for (int y = 0; y < mapSizeY; y++){
    for (int x = 0; x < mapSizeX; x++){
      if (y == 0 || x == 0 || x == mapSizeX-1 || y == mapSizeY-1)
        mapFile << "1";
      else
        mapFile << "0";
      if (x != mapSizeX-1)
        mapFile << ",";
    }
    mapFile << std::endl;
  }
  mapFile.close();
}


void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
  Entity& newTile(manager.AddEntity("Tile"));   //might add the x and y to name it better
  newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);

}
