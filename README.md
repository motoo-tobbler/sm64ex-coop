# sm64ex-coop
Unsanctioned WIP fork for Android. Online multiplayer mod for SM64 that synchronizes all entities and every level for multiple players. Fork of [sm64pc/sm64ex](https://github.com/sm64pc/sm64ex). Contains code copied from [AloXado320/sm64ex-alo](https://github.com/AloXado320/sm64ex-alo), [VDavid003/sm64-port-android](https://github.com/VDavid003/sm64-port-android), and [porcino/sm64-port-android](https://github.com/porcino/sm64-port-android).

Feel free to report bugs and contribute, but remember, there must be **no upload of any copyrighted asset**. 
Run `./extract_assets.py --clean && make clean` or `make distclean` to remove ROM-originated content.

## How to Play on Android

[Click here to read the guide](README_android.md).

What works:

✅ NO root, chroot, or proot required

✅ Direct connection - client and server

✅ GPU acceleration*

✅ Texture, Model, and Lua mods

✅ Touch controls (buggy)

*YMMV

What doesn't work:

❌ Discord

❌ BASS Audio

❌ SurfaceFlinger SDL2 backend

❌ External gamepads

❌ Fullscreen

## How to Play

[Instructions on how to play are available on the wiki.](https://github.com/djoslin0/sm64ex-coop/wiki/How-to-Play)

- The easiest way is to download [coop-compiler](https://github.com/coop-compiler/coop-compiler/releases/latest/download/coop-compiler.exe)

## Goal (accomplished)
Create a mod for the PC port where multiple people can play online together.

Unlike previous online attempts, this one synchronized enemies and events. This allows players to be interacting with the same world at the same time.

## Lua
sm64ex-coop is moddable via lua, similar to how Roblox and Gmod works. To get started, click [here](docs/lua/lua.md) to see the lua documentation

## Discord
[https://discord.gg/TJVKHS4](https://discord.gg/TJVKHS4)
