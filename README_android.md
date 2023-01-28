# How to play `sm64ex-coop` on Android

Video Tutorial:

[![link](https://i.ytimg.com/vi/3B6l8QqMWU4/maxresdefault.jpg)](https://www.youtube.com/watch?v=3B6l8QqMWU4 "[TUTORIAL] How to play sm64ex-coop on Android")

1. Install the F-Droid App Store by going [here](https://f-droid.org/) and touching the "DOWNLOAD F-DROID" button ([source code](https://github.com/f-droid/fdroidclient)). Then touch the file from your downloads:

![image](https://user-images.githubusercontent.com/31490854/207102280-3db84815-53d0-467c-886a-a833be5c8780.png)


2. You might get a warning that "your phone is not allowed to install unknown apps". If you trust F-Droid, touch "SETTINGS":

![image](https://user-images.githubusercontent.com/31490854/207102454-605f0173-4585-41b8-bc77-7045fc9dacdc.png)


3. Then touch to enable "Allow from this source", and touch the back button:

![image](https://user-images.githubusercontent.com/31490854/207102632-2d246eac-a5bc-4e9e-8092-5bcb76b4360f.png)


4. Now you can touch "INSTALL" for F-Droid:

![image](https://user-images.githubusercontent.com/31490854/207102705-d6f27617-a4d7-4ff4-ab7b-9c763be85c8d.png)


5. Open F-Droid and wait for a few minutes. The first time you use F-Droid, it has to download a list of all available apps from the internet. This can take a long time, but when you no longer see "Updating repositories" at the top, it is finished:

![image](https://user-images.githubusercontent.com/31490854/207102841-ddcfef14-73f4-4f03-974c-c986d3c67713.png)


6. Search "Termux" and touch the blue download button on the app that is _exactly_ named "Termux", not any of the others:

![image](https://user-images.githubusercontent.com/31490854/207103001-d0509436-492d-4510-8de5-e45554725407.png)


7. After it has finished downloading, an "INSTALL" button will appear, now touch that ([source code](https://github.com/termux/termux-app)):

![image](https://user-images.githubusercontent.com/31490854/207103108-8568f61f-3b53-4a06-ab97-d42acb7947a8.png)


8. You might see a warning very similar to the one covered in steps 5-7. If you trust Termux, repeat that process.

9. Open Termux and wait until the "installing bootstrap packages" message disappears. Then, the first thing you need to do is type `pkg upgrade -y` and press Enter (or "Go" as some touch keyboards label it):

![image](https://user-images.githubusercontent.com/31490854/209229669-9463d400-878e-40b0-9689-b013140fef61.png)


10. When it is first installed, Termux frequently has outdated mirrors. If you see any errors like these (will have a red `E:`), then type `termux-change-repo` next, and press Enter. If you don't see any errors, or if you see "The default action is to keep your current version" skip to step 14:

![image](https://user-images.githubusercontent.com/31490854/207103444-c206ab3d-5245-4ca4-b392-7930e6db65d7.png)
![image](https://user-images.githubusercontent.com/31490854/207103521-8658e35f-8d7f-4b36-b416-7eda94bfa53a.png)


11. Press Enter again when you see this first screen:

![image](https://user-images.githubusercontent.com/31490854/207103623-82f57c13-c0c9-486b-b3bc-529ff13e4e3a.png)


12. At this screen, use the arrow keys _above_ your normal touch keyboard to navigate up and down, then press Space to select a _different_ mirror, then press Enter to confirm:

![image](https://user-images.githubusercontent.com/31490854/207103874-9ab3eed7-c2c5-47da-89df-1b9e14cc95da.png)


13. The red `E:` should be gone from the black screen with white text; if it's not, repeat steps 10-12 until it's gone. Then, type `pkg upgrade -y` and press Enter:

![image](https://user-images.githubusercontent.com/31490854/207104093-8037ed9f-207d-403b-bc28-262633f167a4.png)


14. You will see repeated messages like this, which end with "The default action is to keep your current version", followed by some letters. Press **Shift -> I -> Enter** every time you see this, because this is a new installation that doesn't contain any custom settings you created:

![image](https://user-images.githubusercontent.com/31490854/207104260-172db617-cc34-4699-a079-d8320ea6c055.png)


15. The `pkg upgrade` will take some time. After it has finished, you will see `~ $` again. Give software running as Termux's Android-assigned user permission to access `/storage/emulated/0`. A popup will appear; touch "ALLOW":

```bash
termux-setup-storage
```

![image](https://user-images.githubusercontent.com/31490854/207105668-f6b8f2c5-7c21-4cd3-999e-c7c3702674e7.png)

16. Install dependencies:

```bash
pkg install x11-repo
pkg install git wget make python getconf zip apksigner clang binutils mesa mesa-dev aapt
```

17. Clone this repository and place your `baserom.us.z64` in it. If you don't already have a `baserom.us.z64`, [here's the guide to obtain one](https://github.com/sanni/cartreader/wiki/What-to-order):

> Replace `/storage/emulated/0/baserom.us.z64` with the current location of your `baserom.us.z64`, or if you don't know the full path, try finding it with the "Amaze" file browser from step 19 and moving it to `/storage/emulated/0` before proceeding.

```bash
git clone https://github.com/robertkirkman/sm64ex-coop.git
cp /storage/emulated/0/baserom.us.z64 sm64ex-coop/baserom.us.z64
cd sm64ex-coop
```

18. Build this `sm64ex-coop` fork. This will take a while. When it is finished, copy the `.apk` to `/storage/emulated/0`:

> If you get a strange error like `make[1]: *** read jobs pipe: Try again.  Stop.`, run `make clean`, then try the build again with `make` instead of `make -j$(nproc)`.

```bash
make -j$(nproc)
cp build/us_pc/sm64.us.apk /storage/emulated/0
```

19. Install "Amaze" ([source code](https://github.com/TeamAmaze/AmazeFileManager)) from F-Droid, open it, and allow all permissions:

![image](https://user-images.githubusercontent.com/31490854/208278959-9b990118-b4a8-4430-bbb1-3f3e5ee5a7b4.png)
![image](https://user-images.githubusercontent.com/31490854/208278964-68161872-54bd-42d7-ac70-7bc43015a514.png)
![image](https://user-images.githubusercontent.com/31490854/208278991-a7626412-a79c-4c69-9955-e90dff263c81.png)
![image](https://user-images.githubusercontent.com/31490854/208278998-dc4c5917-cbf2-4247-a81f-7617c039425c.png)
![image](https://user-images.githubusercontent.com/31490854/208279031-d1816791-3ad6-40fc-b1dd-6b89b6ad0f74.png)

20. Install the `sm64.us.apk` by scrolling to the bottom of the `/storage/emulated/0` folder, touching the `sm64.us.apk`, and allowing all permissions:

![image](https://user-images.githubusercontent.com/31490854/208279102-05600d2d-826e-46f4-8414-b85d13a6260e.png)
![image](https://user-images.githubusercontent.com/31490854/208279123-9065515d-ab40-4422-a260-e12e0c55e0b7.png)
![image](https://user-images.githubusercontent.com/31490854/208279127-4bbdbf8b-d57c-4f28-a256-8e8085dfb0d3.png)
![image](https://user-images.githubusercontent.com/31490854/208279131-903d16e4-d251-486f-bddd-c33a1328c592.png)
![image](https://user-images.githubusercontent.com/31490854/208279184-e5fa1e21-2947-4313-b7f2-0e72f1352d4d.png)
![image](https://user-images.githubusercontent.com/31490854/208279190-d3204ce8-5030-44ca-a044-9c091ec75ea4.png)

21. To play with others online, tell them to follow this guide first, then either port forward or follow the [VPN guide](README_vpn.md).

> To install Lua mods, put them in `/storage/emulated/0/com.owokitty.sm64excoop/user/mods`, or `/storage/emulated/0/Android/data/com.owokitty.sm64excoop/files/user/mods` if you don't accept the storage permission request.
* Default mods:
```bash
cp -r build/us_pc/mods/* /storage/emulated/0/com.owokitty.sm64excoop/user/mods/
```
* Example:
```bash
unzip /storage/emulated/0/twisted-adventures.zip -d /storage/emulated/0/com.owokitty.sm64excoop/user/mods/
```

> To install DynOS packs, put them in `/storage/emulated/0/com.owokitty.sm64excoop/dynos/packs`, or `/storage/emulated/0/Android/data/com.owokitty.sm64excoop/files/dynos/packs` if you don't accept the storage permission request. Texture packs' `gfx` folders also work here as long as they are not too intensive. Create the folder if it doesn't exist already.
* Example:
```bash
pkg install p7zip
mkdir -p /storage/emulated/0/com.owokitty.sm64excoop/dynos/packs/
7z x -o/storage/emulated/0/com.owokitty.sm64excoop/dynos/packs/ /storage/emulated/0/Render96_Chars.rar
```
