#!/data/data/com.termux/files/usr/bin/bash

mkdir SDL

pushd SDL

wget http://libsdl.org/release/SDL2-2.26.1.zip
unzip -q SDL2-2.26.1.zip
mv SDL2-2.26.1/include include
ln -s . include/SDL2
rm SDL2-2.26.1.zip
rm -r SDL2-2.26.1

popd
