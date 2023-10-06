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


class IGit {
public:
  virtual ~IGit() = default;    

  template<typename... Args>
  bool diff_namestatus(FileStatusMap& files, Args... args);
  virtual bool init() = 0;
  virtual bool root(std::string& path) = 0;

protected:
  IGit() = default;
};


class CGitCommand : public IGit {
public:
  CGitCommand(const std::string& gitcli);
  virtual ~CGitCommand() = default;

  virtual bool diff_namestatus(FileStatusMap& files) override;
  virtual bool init() override;
  virtual bool root(std::string& path) override;

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
