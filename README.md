# GitExtended
Set of Git workflows to help with my development experience..

## Prerequisites

### C++20
make sure to have C++20 installed on the machine.

### cmake
Download [cmake](https://cmake.org/download/)

### vcpkg
Install and configure [vcpkg](https://github.com/microsoft/vcpkg#getting-started)

#### Windows
```
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

#### Linux
```
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
```

### Git
We need git to be part of environment. This works automatically on unix. But do this for windows

```cmd
> where git.exe
```
Win+R > sysdm.cpl > Advanced.
Edit the path variable with the above path

## Installation
```cmd
cd GitExtended
cmake -S . -B build
cmake --build build
```

Executable will be available under ./GitExtended/build/gitex/src/Debug.

Add the path to the environment


## Usage
```cmd
gitex -h
```
