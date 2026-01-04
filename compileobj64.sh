#!/bin/sh
x86_64-w64-mingw32-gcc -m64 -c -O2 -fno-ident -ffunction-sections -fdata-sections -DBEA_ENGINE_STATIC -DBEA_USE_STDCALL -D_UCRT -Iinclude -obin/BeaEngineLib64_rdata.obj src/BeaEngine.c
ld -r -T merge_for_delphi.ld --oformat pe-x86-64 -o bin/BeaEngineLib64.obj bin/BeaEngineLib64_rdata.obj
rm bin/BeaEngineLib64_rdata.obj
