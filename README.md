# ABI Change Demo

## Introduction

An ABI breaking change in library can lead to application undefined behavior if the application is not correctly recompiled and linked to the updated library.

## ABI Change Demo

```bash
# Build library V1.
cd library_v1
g++ -g -fdump-lang-class -shared -fPIC library.cpp -I. -o liblibrary.so
cd ..

# Build library V2.
cd library_v2
g++ -g -fdump-lang-class -shared -fPIC library.cpp -I. -o liblibrary.so
cd ..

# Build application.
cd application
# Build application using the header from library V1.
g++ -g -fdump-lang-class -o app_header_v1.o -c app.cpp -I../library_v1
# Build application using the header from library V2.
g++ -g -fdump-lang-class -o app_header_v2.o -c app.cpp -I../library_v2

# Link application to libraries.
# There are no linker errors, suggesting that Rectangle::area() that is
# used in the app.cpp have been successfully found.
# Link application using the header from library V1 correctly with library V1.
g++ -o app_header_v1_library_v1.app app_header_v1.o -L../library_v1 -llibrary
# Link application using the header from library V2 correctly with library V2.
g++ -o app_header_v2_library_v2.app app_header_v2.o -L../library_v2 -llibrary
# Link application using the header from library V1 correctly with library V2.
# ABI breaking change (vtable conflict)
g++ -o app_header_v1_library_v2.app app_header_v1.o -L../library_v2 -llibrary
# Link application using the header from library V2 correctly with library V1.
# ABI breaking change (vtable conflict)
g++ -o app_header_v2_library_v1.app app_header_v2.o -L../library_v1 -llibrary

# This works as expected.
LD_LIBRARY_PATH=../library_v1 ./app_header_v1_library_v1.app
# This does not work.
# Segmentation fault (core dumped)
LD_LIBRARY_PATH=../library_v1 ./app_header_v2_library_v1.app
# This works as expected.
LD_LIBRARY_PATH=../library_v2 ./app_header_v2_library_v2.app
# This does not work.
# Area: 16
# terminate called after throwing an instance of 'std::runtime_error'
#   what():  Area is not correct.
# Aborted (core dumped)
LD_LIBRARY_PATH=../library_v2 ./app_header_v1_library_v2.app

cd ..
```
