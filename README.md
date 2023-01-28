# sm64ex-coop
Unsanctioned WIP fork for Android and other open-source UNIX-like operating systems that are not supported by the normal `sm64ex-coop`, plus improved touchscreen controls. Online multiplayer mod for SM64 that synchronizes all entities and every level for multiple players. Fork of [sm64pc/sm64ex](https://github.com/sm64pc/sm64ex). Contains code copied from [AloXado320/sm64ex-alo](https://github.com/AloXado320/sm64ex-alo), [VDavid003/sm64-port-android](https://github.com/VDavid003/sm64-port-android), [VDavid003/sm64-port-android-base](https://github.com/VDavid003/sm64-port-android-base), and [porcino/sm64-port-android](https://github.com/porcino/sm64-port-android).

Feel free to report bugs and contribute, but remember, there must be **no upload of any copyrighted asset**. 
Run `./extract_assets.py --clean && make clean` or `make distclean` to remove ROM-originated content.

## How to Play on Android

[Click here to read the guide for Android](README_android.md).

[Click here to build the `.apk` from a non-Android device](https://github.com/robertkirkman/sm64ex-coop-android-base). 

Recording showcasing new touch controls features:

[sm64ex-coop-android.webm](https://user-images.githubusercontent.com/31490854/213303280-b4a160a6-f711-4497-b9e1-d463546048e1.webm)

All custom icons by **xLuigiGamerx#6999**!

What works:

✅ Direct connection - client and server ([VPN guide here](README_vpn.md))

✅ GPU acceleration

✅ Normal audio

✅ (most) DynOS and Lua mods

✅ Touch controls

✅ Fullscreen

✅ External gamepads

What doesn't work:

❌ Some Lua mods on some devices

❌ Crash when "skip intro cutscene" option is used on some devices

❌ Inconsistent crashes in Peach's Castle on some devices

❌ Occasional crash when loading HD texture packs - try restarting app

❌ Discord

❌ BASS audio

## How to Play on any open-source UNIX-like OS

This repository also contains changes meant to make porting `sm64ex-coop` to open-source UNIX-like operating systems easier (the normal `sm64ex-coop` only supports GNU/Linux and MacOS at the exclusion of others). On many of them, setting up the dependencies (a C and C++ preprocessor and compiler, GNU Make, binutils, Python 3, SDL2, GLEW, an OpenGL or OpenGL ES graphics driver, and an X11-compatible display server) can take many steps that vary dramatically, so I've decided not to make a complete walkthrough for every single one like I have for Android. Once you have all of those configured just right, though, you'll be able to compile and play this way, and hopefully you'll only need to make minor adjustments to the `Makefile` to detect the dependencies the way your OS needs it to.

```
git clone https://github.com/robertkirkman/sm64ex-coop.git
cp /path/to/baserom.us.z64 sm64ex-coop/baserom.us.z64
cd sm64ex-coop
TOUCH_CONTROLS=1 make -j$(nproc)
build/us_pc/sm64.us.f3dex2e
```

To get you started, I've confirmed my fork to work on the following operating systems (as well as GNU/Linux), and have commited initial changes for them:

✅ postmarketOS

✅ OpenBSD

There are some bugs when running on them, but I've fixed just enough to get `sm64ex-coop` to compile, launch and host servers with mods in a playable state on them. I strongly suspect that if your device has a non-`amd64` architecture and you find bugs, you'll probably want to look through my "`__ANDROID__`" `#ifdef`s in the code and check whether the code I've placed in them turns out to be architecture-related rather than Android-related.

## How to Play on Windows

[Instructions on how to play are available on the wiki.](https://github.com/djoslin0/sm64ex-coop/wiki/How-to-Play)

- The easiest way is to download [coop-compiler](https://github.com/coop-compiler/coop-compiler/releases/latest/download/coop-compiler.exe)

## Goal (accomplished)
Create a mod for the PC port where multiple people can play online together.

Unlike previous online attempts, this one synchronized enemies and events. This allows players to be interacting with the same world at the same time.

## Lua
sm64ex-coop is moddable via lua, similar to how Roblox and Gmod works. To get started, click [here](docs/lua/lua.md) to see the lua documentation

## Discord
[https://discord.gg/TJVKHS4](https://discord.gg/TJVKHS4)
