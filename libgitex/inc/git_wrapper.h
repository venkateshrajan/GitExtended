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

  virtual bool diff_namestatus(FileStatusMap& files, 
                       const std::list<std::string>& arguments) = 0;
  virtual bool init(const std::list<std::string>& arguments) = 0;
  virtual bool root(std::string& path, const std::list<std::string>& arguments) = 0;

protected:
  IGit() = default;
};


class CGitCommand : public IGit {
public:
  CGitCommand(const std::string& gitcli);
  virtual ~CGitCommand() = default;

  virtual bool diff_namestatus(FileStatusMap& files,
                       const std::list<std::string>& arguments) override;

  virtual bool init(const std::list<std::string>& arguments) override;
  virtual bool root(std::string& path, 
                    const std::list<std::string>& arguments) override;

protected:
  bool parse_status(const std::vector<std::string>& files, 
                    FileStatusMap& files_with_status);

protected:
  std::string gitcli;
};


}
