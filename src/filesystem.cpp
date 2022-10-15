#include "filesystem.hpp"

namespace gui 
{
  FileSystem& FileSystem::GetInstance()
  {
    static FileSystem s_instace;
    return s_instace;
  }

  const std::filesystem::path& FileSystem::GetGameWorkspacePath() const
  {
    return m_workSpacePath;
  }

  void FileSystem::SetGameWorkspacePath(const std::string& path)
  {
    m_workSpacePath = path;
  }
  
  const std::string FileSystem::GetAbsolutePath(const std::string& path) const
  {
    return m_workSpacePath / path;
  }
} // namespace gameng
