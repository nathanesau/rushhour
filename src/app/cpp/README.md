# RushHour App (C++)

## CMake Build Instructions

I use CMake for creating a debug build of the game. Instructions are below.

```bash
# windows: install Qt using vcpkg on windows
# ubuntu: install Qt using ``sudo apt-get install qt5-default``
mkdir build
cd build
cmake ..
make

# run the game
./rushhour
```

## Web Assembly Instructions

Use the following commands to compile the game for Web Assembly. Note that the Web Assembly version of the game is deployed to GitHub pages.

```bash
# build the app
mkdir wasm-build
docker run -v "F:/rushhour/src/app/cpp/wasm-build":/project/build -v "F:/rushhour/src/app/cpp":/project/source maukalinow/qtwasm_builder:5.14_latest

# run local webserver and open wasm-build/rushhour.html
python -m http.server
```

## Windows x86 Static Instructions

Use the following commands to compile the game for Windows x86 static.

```bash
# build the app
docker run --rm -it -v "F:/rushhour/src/app/cpp":/app docker.pkg.github.com/nathanesau/docker-qt/qt-win32s:1.0
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
docker run --rm -it -v "F:/rushhour/src/app/cpp":/app docker.pkg.github.com/nathanesau/docker-qt/qt-win64s:1.0
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
docker run --rm -it -v "F:/rushhour/src/app/cpp":/app docker.pkg.github.com/nathanesau/docker-qt/qt-static:1.0
cd /app
qmake
make -j $(nproc)

# run the app
./release/rushhour
```
