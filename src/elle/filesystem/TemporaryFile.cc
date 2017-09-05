#include <elle/filesystem/TemporaryFile.hh>

namespace elle
{
  namespace filesystem
  {
    TemporaryFile::TemporaryFile(std::string const& name)
      : _path{_directory.path() / name}
    {
      // Check that it is ok.
      fs::ofstream(this->_path);
    }
  }
}
