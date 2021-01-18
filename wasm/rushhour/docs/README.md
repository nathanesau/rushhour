# build instructions

## install qt

```bash
# run from vcpkg directory
# installs about 30 packages, takes about 1 hour
# about 12GB of disk space used
./vcpkg.exe install qt5:x86:windows

# required in order to use vcpkg with Visual Studio
./vcpkg.exe integrate install
```