#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
private:
  std::string textureId;
  int scale;
  int tileSize;
public:
  Map(std::string textureId, int scale, int tileSize);
  ~Map();
  void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
  void AddTile(int sourceX, int sourceY, int x, int y);
  void CreateMap(std::string filePath, int mapSizeX, int mapSizeY);
  void UpdateMap(std::string filePath, int mapSizeX, int mapSizeY, int toChangeX, int toChangeY);
};

#endif
