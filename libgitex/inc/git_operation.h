#pragma once

namespace gitex {

class IGit;

class IGitOperation {
public:
  virtual ~IGitOperation() = default;

  virtual bool run(const std::vector<std::string>& arguments);

protected:
  IGitOperation();

  virtual bool prepare(const std::vector<std::string>& arguments);
  virtual bool process(const std::vector<std::string>& arguments) = 0;
  virtual bool finalize(const std::vector<std::string>& arguments);

  std::shared_ptr<IGit> git;
  std::string root;
};

class CGitDiffOperation : public IGitOperation{
public:
  CGitDiffOperation(const std::string& path);

protected:
  virtual bool process(const std::vector<std::string>& arguments) override;

  std::string copyPath;
};

}
