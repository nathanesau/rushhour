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

## Build Instructions (WASM)

use this docker image https://hub.docker.com/r/maukalinow/qtwasm_builder.

```bash
mkdir build

# build the app
docker run -v /home/esna0001/rushhour/wasm/build-wasm:/project/build -v /home/esna0001/rushhour/wasm/rushhour:/project/source maukalinow/qtwasm_builder:5.14_latest

# NOTE: QLabel clicks are not working properly
python3 -m http.server
```