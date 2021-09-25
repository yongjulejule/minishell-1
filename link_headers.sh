#! /bin/sh

rm src/*.h src/pipe/*.h src/*.h src/builtin/*.h
ln include/*.h src
ln include/*.h src/pipe
ln include/*.h src/builtin
