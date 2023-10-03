#pragma once

namespace gitex {

class IGit;

class IGitOperation {
public:
  virtual ~IGitOperation() = default;

  virtual bool run();

protected:
  IGitOperation();

  virtual bool prepare() = 0;
  virtual bool process() = 0;
  virtual bool finalize() = 0;

  std::shared_ptr<IGit> git;
};

class CGitDiffOperation : public IGitOperation{
public:
  CGitDiffOperation();

protected:
  virtual bool prepare() override;
  virtual bool process() override;
  virtual bool finalize() override;

  std::string root;
};

}
