# wasm

## Build Info

use one of these:

* rushhour/CMakeLists.txt (cmake) 
* rushhour/rushhour.pro (qmake)

## Folder Info

folder structure:

* rushhour: Qt Application (written in C++)

## Emscripten Info

emscripten instructions:

```powershell
git clone "https://github.com/emscripten-core/emsdk.git"

# install
.\emsdk.bat install latest

# activate
.\emsdk activate latest

# activate PATH and other variables in current terminal
.\emsdk_env.bat
```