#pragma once

namespace gitex {

class IGit;


class IGitOperation {
public:
  virtual ~IGitOperation() = default;

  virtual bool run(const std::list<std::string>& arguments);

protected:
  IGitOperation();

  virtual bool prepare(const std::list<std::string>& arguments);
  virtual bool process(const std::list<std::string>& arguments) = 0;
  virtual bool finalize(const std::list<std::string>& arguments);
  bool copy_item(const std::string& item, const std::string& path);

  std::shared_ptr<IGit> git;
  std::string root;
};


class CGitDiffOperation : public IGitOperation{
public:
  CGitDiffOperation(const std::string& path);

protected:
  virtual bool process(const std::list<std::string>& arguments) override;

  std::string copyPath;
};


class CGitCopyOperation : public IGitOperation{
public:
  CGitCopyOperation(const std::string& inputfile, const std::string& path);

protected:
  virtual bool process(const std::list<std::string>& arguments) override;

  std::string inputfile;
  std::string copyPath;
};

}
