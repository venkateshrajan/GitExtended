#include "pch.h"
#include "git_operation.h"

#include "git_wrapper.h"
#include "glog/logging.h"
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <string>

namespace gitex {

#define CVS "CVS"

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

bool IGitOperation::copy_item(const std::string& item, const std::string& path) {
  std::filesystem::path src(root);
  src /= std::filesystem::path(item);
  std::filesystem::path dest(path);
  dest /= std::filesystem::path(item);

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
    src_cvs /= std::filesystem::path(CVS);
    std::filesystem::path dest_cvs = dest.parent_path();
    dest_cvs /= std::filesystem::path(CVS);
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
    LOG(INFO) << "Processing " << relPath << " with status " << itemStatus;
    if (!copy_item(relPath, copyPath)) continue;
  }

  LOG(INFO) << "Completed the diff command successfully";
  return true;
}



CGitCopyOperation::CGitCopyOperation(const std::string& inputfile, const std::string& path) :
  IGitOperation(),
  inputfile(inputfile),
  copyPath(path) {
  
}


bool CGitCopyOperation::process(const std::list<std::string>& arguments)  {
  std::ifstream ifs;
  ifs.open(inputfile);
  if (!ifs.good()) {
    LOG(ERROR) << "Failed to open input file" << inputfile;
    return false;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    boost::trim(line);
    LOG(INFO) << "Processing " << line;
    if (!copy_item(line, copyPath)) continue;
  }

  LOG(INFO) << "Completed the diff command successfully";
  return true;
}


}
