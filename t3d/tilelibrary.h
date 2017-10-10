#ifndef T3D_TILELIBRARY_H
#define T3D_TILELIBRARY_H

#include <string>
#include <vector>

#include "core/aabb.h"
#include "render/compiledmesh.h"

class Tile
{
 public:
  Tile();
  ~Tile();

  std::string path;
  Aabb        aabb;
  std::string name;

  std::shared_ptr<CompiledMesh> mesh;
};

class TileLibrary
{
 public:
  void
  AddDirectory(const std::string& directory_path);

  void
  AddFile(const std::string& current_directory, const std::string& path);

  std::vector<std::shared_ptr<Tile>> tiles;
};

#endif  // T3D_TILELIBRARY_H
