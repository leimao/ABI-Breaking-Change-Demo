# ABI Change Demo

## Introduction

An ABI change in library can lead to application undefined behavior if the application is not recompiled and linked to the updated library.

## ABI Change Demo

```bash
# Build library V1.
cd library_v1
g++ -shared -fPIC library.cpp -I. -o liblibrary.so
cd ..

# Build library V2.
cd library_v2
g++ -shared -fPIC library.cpp -I. -o liblibrary.so
cd ..

# Build and run application.
cd application

# Build application that links to library V1 and
# the vtable for the Shape class is from library V1.
g++ -o app.app app.cpp -I../library_v1 -L../library_v1 -llibrary
# Run application that links to library V1 with library V1 loaded at runtime.
LD_LIBRARY_PATH=../library_v1 ./app.app
# Run application that links to library V1 with library V2 loaded at runtime.
# This leads to undefined behavior due to ABI change and
# incorrect/inappropriate overridden function is called
# via the library incompatible vtable.
LD_LIBRARY_PATH=../library_v2 ./app.app

# Build application that links to library V2 and
# the vtable for the Shape class is from library V2.
g++ -o app.app app.cpp -I../library_v2 -L../library_v2 -llibrary
# Run application that links to library V2 with library V2 loaded at runtime.
LD_LIBRARY_PATH=../library_v2 ./app.app
# Run application that links to library V2 with library V1 loaded at runtime.
# This leads to undefined behavior due to ABI change and
# incorrect/inappropriate overridden function is called
# via the library incompatible vtable.
LD_LIBRARY_PATH=../library_v1 ./app.app

cd ..
```