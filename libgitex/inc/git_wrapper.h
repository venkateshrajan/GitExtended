#pragma once

namespace gitex {

enum status {
  status_modified,
  status_copy_edit,
  status_rename_edit,
  status_added,
  status_deleted,
  status_unmerged
};

typedef std::unordered_map<std::string, status> FileStatusMap;

class IGitOp {
public:
  virtual ~IGitOp() = default;    

  virtual bool diff_namestatus(FileStatusMap& files) = 0;
  virtual bool init() = 0;

protected:
  IGitOp() = default;
};


class CCommandGitOp : public IGitOp {
public:
  CCommandGitOp(const std::string& gitcli);
  virtual ~CCommandGitOp() = default;

  virtual bool diff_namestatus(FileStatusMap& files) override;
  virtual bool init() override;

protected:
  template<typename... Args>
  int runCommand(std::vector<std::string>& output,
                 std::vector<std::string>& error,
                 Args... args);

  bool parse_status(const std::vector<std::string>& files, 
                    FileStatusMap& files_with_status);

protected:
  std::string gitcli;
};

}
