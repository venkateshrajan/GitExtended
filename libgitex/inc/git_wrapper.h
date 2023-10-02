#pragma once

namespace gitex {

class IGitOp {
public:
  virtual ~IGitOp() = default;    

  virtual bool diff_nameonly(std::vector<std::string>& files) = 0;
  virtual bool init() = 0;

protected:
  IGitOp() = default;
};

class CCommandGitOp : public IGitOp {
public:
  CCommandGitOp(const std::string& gitcli);
  virtual ~CCommandGitOp() = default;

  virtual bool diff_nameonly(std::vector<std::string>& files) override;
  virtual bool init() override;

protected:
  bool runCommand(const std::string& command, std::vector<std::string>& output);

protected:
  std::string gitcli;
};

}
