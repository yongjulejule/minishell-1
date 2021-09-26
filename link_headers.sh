#! /bin/sh

rm src/*.h src/exec/*.h src/redir/*.h src/*.h src/builtin/*.h
ln include/*.h src/
ln include/*.h src/exec/
ln include/*.h src/redir/
ln include/*.h src/builtin/
