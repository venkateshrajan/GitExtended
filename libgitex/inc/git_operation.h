#pragma once

namespace gitex {

class IGit;

class IGitOperation {
public:
  virtual ~IGitOperation() = default;

  virtual bool run();

protected:
  IGitOperation();

  virtual bool prepare();
  virtual bool process() = 0;
  virtual bool finalize();

  std::shared_ptr<IGit> git;
  std::string root;
};

class CGitDiffOperation : public IGitOperation{
public:
  CGitDiffOperation(const std::string& path);

protected:
  virtual bool process() override;

  std::string copyPath;
};

}
