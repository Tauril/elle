#pragma once

#include <functional>
#include <vector>

#include <boost/optional.hpp>

#include <elle/compiler.hh>
#include <elle/filesystem.hh>

namespace elle
{
  namespace archive
  {
    enum class Format
    {
      zip,
      tar,
      tar_gzip,
      tar_bzip2,
      zip_uncompressed
    };

    using Renamer =
      std::function<boost::filesystem::path(boost::filesystem::path const&)>;
    /// Returns true to exclude the file
    using Excluder =
      std::function<bool(boost::filesystem::path const&)>;

    ELLE_API
    void
    archive(Format format,
            std::vector<boost::filesystem::path> const& files,
            boost::filesystem::path const& path,
            Renamer const& renamer = Renamer(),
            Excluder const& excluder = Excluder(),
            bool ignore_failure = false);

    /// The extract function supports all formats, no need to specify it
    ELLE_API
    void
    extract(boost::filesystem::path const& archive,
            boost::optional<boost::filesystem::path> const& output = boost::none);
  }
}
