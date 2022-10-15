#pragma once

#include <filesystem>
#include <string>

namespace gui 
{

class FileSystem
{
public:
  static FileSystem& GetInstance(); 
  void SetGameWorkspacePath(const std::string& path);
  const std::filesystem::path& GetGameWorkspacePath() const;
  const std::string GetAbsolutePath(const std::string& path) const;
private:
  std::filesystem::path m_workSpacePath = "/home/kristoft/dev/repos/signalgui";
};

} // namespace gameng
