#include "pch.h"
#include "git_operation.h"

#include "git_wrapper.h"
#include "glog/logging.h"

namespace gitex {

IGitOperation::IGitOperation() {
  git = std::make_shared<CGitCommand>("git");
}


bool IGitOperation::run(const std::list<std::string>& arguments) {
  if (!prepare(arguments)) {
    LOG(ERROR) << "Prepare failed";
    return false;
  }

  if (!process(arguments)) {
    LOG(ERROR) << "Process failed";
    return false;
  }

  if (!finalize(arguments)) {
    LOG(ERROR) << "Finalize failed";
    return false;
  }

  return true;
}


bool IGitOperation::prepare(const std::list<std::string>& arguments) {
  if (!git->root(root, {})) {
    LOG(ERROR) << "Failed to get repo root";
    return false;
  }

  return true;
}


bool IGitOperation::finalize(const std::list<std::string>& arguments) {
  return true;
}



CGitDiffOperation::CGitDiffOperation(const std::string& copyPath) :
  IGitOperation(),
  copyPath(copyPath) {
  
}


bool CGitDiffOperation::process(const std::list<std::string>& arguments)  {
  gitex::FileStatusMap files;
  if (!git->diff_namestatus(files, arguments)) {
    LOG(ERROR) << "Failed to get diff";
    return false;
  }

  for (auto const & [relPath, itemStatus]: files) {
    if (itemStatus == status_deleted) {
      LOG(INFO) << "Skipping " << relPath << " as it is a deleted";
      continue;
    }

    LOG(INFO) << "Processing " << relPath << " with status " << itemStatus;

    if (!process_item(relPath)) continue;
  }

  return true;
}


bool CGitDiffOperation::process_item(const std::string& rel_path) {
  std::filesystem::path src(root);
  src /= std::filesystem::path(rel_path);
  std::filesystem::path dest(copyPath);
  dest /= std::filesystem::path(rel_path);

  LOG(INFO) << "Copying " << src.string() << " to " << dest.string();
  if (!std::filesystem::exists(src)) {
    LOG(ERROR) << "File/directory " << src.string() << " does not exists";
    return false;
  }

  // create missing directories
  if (!std::filesystem::is_directory(dest) 
    && dest.has_parent_path() 
    && !std::filesystem::exists(dest.parent_path()) 
    && !std::filesystem::create_directories(dest.parent_path())) {
    LOG(ERROR) << "Failed to create directories " << dest.parent_path().string();
    return false;
  }

  std::filesystem::copy_options co = 
    std::filesystem::copy_options::update_existing |
    std::filesystem::copy_options::recursive;

  std::error_code ec;
  std::filesystem::copy(src, dest, co, ec);
  if (ec) {
    LOG(ERROR) << "Copy failed. Code: " << ec.value() 
      << " Message: " << ec.message();
    return false;
  } else {
    LOG(INFO) << "Copied " << dest.string();
  }

  // copy cvs directory for this item
  if (!std::filesystem::is_directory(src)) {
    std::filesystem::path src_cvs = src.parent_path();
    src_cvs /= std::filesystem::path(get_cvs_directory_name());
    std::filesystem::path dest_cvs = dest.parent_path();
    dest_cvs /= std::filesystem::path(get_cvs_directory_name());
    if (std::filesystem::exists(src_cvs)) {
      std::filesystem::copy(src_cvs, dest_cvs, co, ec);
      if (ec) {
        LOG(ERROR) << "Copy failed for CVS. Code: " << ec.value() 
          << " Message: " << ec.message();
        return false;
      } else {
        LOG(INFO) << "Copied " << dest_cvs.string();
      }
    }
  } else {
    // TODO: copy cvs directory for all the sub directoies
  }

  return true;
}


std::string CGitDiffOperation::get_cvs_directory_name() {
#if defined(_WIN32)
  return "CVS";
#else
  return ".CVS";
#endif
}


}
