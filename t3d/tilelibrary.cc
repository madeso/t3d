#include "t3d/tilelibrary.h"

#include "core/os.h"
#include "core/mesh.h"
#include "core/filesystem.h"
#include "core/log.h"

LOG_SPECIFY_DEFAULT_LOGGER("tile_library")

Tile::Tile()
    : aabb(Aabb::Empty())
{
}

Tile::~Tile()
{
}

void
TileLibrary::AddDirectory(const std::string& directory_path)
{
  const auto directory = ListDirectory(directory_path);
  for(const auto& file : directory.files)
  {
    if(GetExtension(file) == ".obj")
    {
      AddFile(directory_path, JoinPath(directory_path, file));
    }
  }
}

void
TileLibrary::AddFile(
    const std::string& current_directory, const std::string& path)
{
  FileSystem file_system;
  FileSystemRootFolder::AddRoot(&file_system, current_directory);
  const auto loaded_mesh = meshes::LoadMesh(&file_system, path);
  if(!loaded_mesh.error.empty())
  {
    LOG_WARN("Failed to open " << path << ": " << loaded_mesh.error);
    return;
  }

  auto tile  = std::make_shared<Tile>();
  tile->path = path;
  tile->name = GetFileNameWithoutExtension(path);
  tile->aabb = loaded_mesh.mesh.CalculateAabb();
  tiles.push_back(tile);
}
