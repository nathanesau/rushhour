# wasm

## Build Instructions (Desktop)

use one of these:

* rushhour/CMakeLists.txt (cmake) 
* rushhour/rushhour.pro (qmake)

for example:

```bash
# build
cd rushhour
qmake -project
qmake
make

# run
./rushhour
```

## Build Instructions (Windows)

use the ``docker.pkg.github.com/nathanesau/docker-qt/qt-win64s:1.0`` docker image.

```bash
# build the app (outputs to rushhour/release/rushhour.exe)
docker run --rm -it -v "F:/rushhour/wasm/rushhour":/app docker.pkg.github.com/nathanesau/docker-qt/qt-win64s:1.0
cd /app
make -j $(nproc)
```

## Build Instructions (WASM)

use the ``maukalinow/qtwasm_builder:5.14_latest`` docker image.

```bash
mkdir build

# build the app
docker run -v /home/esna0001/rushhour/wasm/build-wasm:/project/build -v /home/esna0001/rushhour/wasm/rushhour:/project/source maukalinow/qtwasm_builder:5.14_latest

# NOTE: QLabel clicks are not working properly
python3 -m http.server
```