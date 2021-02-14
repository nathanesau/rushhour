# RushHour App (C++)

## CMake Build Instructions

CMake is used for:

* building game on Windows (must first install ``Qt`` using vcpkg)
* builing tests on Ubuntu (must first install ``libgtest-dev``)

```bash
# build the project (for Windows, review ``VcpkgPath`` in src/CMakeLists.txt)
mkdir build
cd build
cmake ..
make

# run the game (Windows)
"build/src/Debug/rushhour.exe"

# run the tests (Ubuntu)
build/test/tests
```

## Web Assembly Instructions

Use the following commands to compile the game for Web Assembly. Note that the Web Assembly version of the game is deployed to GitHub pages.

```bash
# build the app
cd src
mkdir wasm-build
docker run -v "F:/rushhour/app/cpp/src/wasm-build":/project/build -v "F:/rushhour/app/cpp/src":/project/source maukalinow/qtwasm_builder:5.14_latest

# run local webserver and open wasm-build/rushhour.html
python -m http.server
```

## Windows x86 Static Instructions

Use the following commands to compile the game for Windows x86 static.

```bash
# build the app
docker run --rm -it -v "F:/rushhour/app/cpp/src":/app docker.pkg.github.com/nathanesau/docker-qt/qt-win32s:1.0
cd /app
qmake
make -j $(nproc)

# run the app
"release/rushhour.exe"
```

## Windows x64 Static Instructions

Use the following commands to compile the game for Windows x64 static.

```bash
# build the app
docker run --rm -it -v "F:/rushhour/app/cpp/src":/app docker.pkg.github.com/nathanesau/docker-qt/qt-win64s:1.0
cd /app
qmake
make -j $(nproc)

# run the app
"release/rushhour.exe"
```

## Linux x64 Static Instructions

Use the following commands to compile the game for Linux x64 static.

```bash
# build the app
docker run --rm -it -v "F:/rushhour/app/cpp/src":/app docker.pkg.github.com/nathanesau/docker-qt/qt-static:1.0
cd /app
qmake
make -j $(nproc)

# run the app
./release/rushhour
```
