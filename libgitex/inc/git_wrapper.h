#pragma once

namespace gitex {

class IGitOp {
public:
  virtual ~IGitOp() = default;    

  virtual bool diff_namestatus(std::vector<std::string>& files) = 0;
  virtual bool init() = 0;

protected:
  IGitOp() = default;
};


class CCommandGitOp : public IGitOp {
public:
  CCommandGitOp(const std::string& gitcli);
  virtual ~CCommandGitOp() = default;

  virtual bool diff_namestatus(std::vector<std::string>& files) override;
  virtual bool init() override;

protected:
  template<typename... Args>
  int runCommand(std::vector<std::string>& output,
                 std::vector<std::string>& error,
                 Args... args);

protected:
  std::string gitcli;
};

}
