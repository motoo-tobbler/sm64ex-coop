# How to play `sm64ex-coop` on Android

### This is also a tutorial for a bunch of other stuff first

GPU acceleration compatibility depends on your device. For simplicity, I will divide all Android devices into three groups, which I describe as follows:

- Class A: Full Vulkan support

- Class B: Partial Vulkan support

- Class C: No Vulkan support

The following steps will help you determine which class your device falls into, and subsequent steps will give slightly different directions for Class A and Class B. **At this time, Class C devices are outside the scope of this guide, and Class B devices _might_ work but are less likely to work than Class A.** This might change in a future update - this guide covers a method involving the [Zink](https://docs.mesa3d.org/drivers/zink.html) graphics driver, but another custom graphics driver known as [GL4ES](https://github.com/ptitSeb/gl4es) exists that does _not_ require Vulkan support, which might help those who encounter problems with the method described here. I'll eventually attempt to use GL4ES with this project, and if it works I will add steps for it here.

1. On the Android device, go [here](https://vulkan.gpuinfo.org/download.php) and download and install the latest `.apk` for Android ([source code](https://github.com/SaschaWillems/VulkanCapsViewer)). Alternatively, you can open Google Play and search for "vulkan info" and install the first result, which should be "Hardware CapsViewer":

   If you have encounter a message like "This app isn't compatible with your phone", are unable to see the app on Google Play, or are using Android 6 or below, you probably have a Class C device. Unfortunately there's a gray area where I'm not sure how to definitively check this if you can't install this app, but you can google "[your device name] vulkan" to try to find out whether there's a chance you have a Class B device.

2. Open the app and touch the "Properties" drop-down menu, then touch "Extensions":

3. This list will appear. If you can find **all** of the following here, then you have a Class A device:

- `VK_KHR_xcb_surface`

- `VK_KHR_imageless_framebuffer`

- `VK_KHR_timeline_semaphore`

- `VK_KHR_create_renderpass2`

  If any of them are missing, but the list isn't empty, then you have a Class B device. 

4. Install the F-Droid App Store by going [here](https://f-droid.org/) and touching the "DOWNLOAD F-DROID" button ([source code](https://github.com/f-droid/fdroidclient)). Then touch the file from your downloads:

5. You might get a warning that "your phone is not allowed to install unknown apps". If you trust F-Droid, touch "SETTINGS":

6. Then touch to enable "Allow from this source", and touch the back button:

7. Now you can touch "INSTALL" for F-Droid:

8. Open F-Droid and wait for a few minutes. The first time you use F-Droid, it has to download a list of all available apps from the internet. This can take a long time, but when you no longer see "Updating repositories" at the top, it is finished:

9. Search "Termux" and touch the blue download button on the app that is _exactly_ named "Termux", not any of the others:

10. After it has finished downloading, an "INSTALL" button will appear, now touch that ([source code](https://github.com/termux/termux-app)):

11. You might see a warning very similar to the one covered in steps 5-7. If you trust Termux, repeat that process.

12. Also from F-Droid, another app you will need much later is "Hacker's Keyboard". You don't need to switch your touch keyboard to it right now, but it might be convenient to install it now. Search for it in F-Droid and install it.

13. Open Termux and wait until the "installing bootstrap packages" message disappears. Then, the first thing you need to do is type `pkg update` and press Enter (or "Go" as some touch keyboards label it):

14. When it is first installed, Termux frequently has outdated mirrors. If you see any errors like these (will have a red `E:`), then type `termux-change-repo` next, and press Enter. If you don't see any errors, skip to step 17:

15. Press Enter again when you see this first screen:

16. At this screen, use the arrow keys _above_ your normal touch keyboard to navigate up and down, then press Space to select a _different_ mirror, then press Enter to confirm:

17. The red `E:` should be gone from the black screen with white text; if it's not, repeat steps 14-16 until it's gone. Then, type `pkg upgrade -y` and press Enter:

18. You will see repeated messages like this, which end with "The default action is to keep your current version", followed by some letters. Press **Shift -> I -> Enter** every time you see this, because this is a new installation that doesn't contain any custom settings you created:

19. The `pkg upgrade` will take some time. After it has finished, you will see `~ $` again. These next few steps are aimed towards connecting a desktop or laptop with a large keyboard to your Android device so that you can type, copy, paste, and run the commands in the later steps more quickly. If you have or prefer to use only one device, then you can skip to step 26, and all of the later commands will work the same when typed directly into the Termux app. Type `pkg install openssh -y` and press Enter:

20. When you can see `~ $` again, type `passwd` and press Enter. You should now type and confirm a new password that you can remember. This is the password you will type to connect from the other device. **`passwd` (and for later, `ssh` too) do not show the characters you type, so if you think you mistyped, you should try pressing backspace a lot of times and start over, before pressing Enter**:

21. There are a few ways you can connect. If you want to connect over **Wi-Fi**, you just need to be connected to the same router on both devices, or if your Android device supports it you could enable "Mobile Hotspot" in Android settings and connect your other device to the resulting network. If you want to connect over **USB**, you can use either RNDIS or ADB protocol, and the connection might be less stuttery, but you will have to keep the Android device plugged into the other device. For RNDIS, you would need to enable "USB tethering" in Android settings, and for ADB, you would have to enable Android Developer Mode, enable USB Debugging, install [ADB Tools](https://developer.android.com/studio/command-line/adb) onto the other device, and run the `adb forward tcp:8022 tcp:8022` command on that device. **To keep this guide from being even longer, I will only cover the Wi-Fi connection here**.

22. Install the `ip` command with `pkg install iproute2 -y`, then type `ip a` and swipe down to scroll up slightly. You need to look for an IPv4 address of the form `X.X.X.X` located in between two instances of a string that may or may not be "`wlan0`". Unfortunately it can be a bit hard to find here, so if you can't find it, check that you are connected to Wi-Fi, and you should also be able to see it in Android Settings -> Connections -> Wi-Fi -> Gear icon near the connected SSID -> IP Address. This is the IP address you will type to connect from the other device:

23. On the other device, open a terminal that has access to the `ssh` command. If the other device has Windows 10 or 11, MacOS or GNU/Linux, it is probably already installed and easily accessible by opening a PowerShell or XTerm window. If it has an older version of Windows, you can use [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) ([source code](https://git.tartarus.org/?p=simon/putty.git;a=tree)), which has different syntax but is compatible with OpenSSH servers and isn't too hard to figure out.

24. Type `sshd` on the Termux app, then on the other device, type `ssh -p 8022 X.X.X.X` where you replace "`X.X.X.X`" with the IP Address you found in step 22, then press Enter.

25. Type "`yes`" to confirm connecting to a new device, then type the password you chose in step 20, and press Enter. You should now see the Termux MOTD (welcome message) and `~ $`. From this point, commands for running in Termux will be placed in code blocks, so that Github gives them copy buttons for easily pasting into this window. Unfortunately, the button to paste into terminal varies wildly by client OS, but on Windows you can try right click.

26. Give software running as Termux's Android-assigned user permission to access `/storage/emulated/0`. A popup will appear; touch "ALLOW":

```bash
termux-setup-storage
```

27. The next app you need (Termux:X11) ([source code](https://github.com/termux/termux-x11)) requires you to be logged into a Github account to download precompiled binaries. If you already have a Github account, just log into it on a browser on the Android device and skip to step 31. It is also possible to compile from source, but if you don't have Android SDK installed then it is probably faster to create a new Github account, which is what the next steps will walk through.

28. Go to https://github.com/login and touch "Create an account" at the bottom:

29. Enter a throwaway email address and password of your choice:

30. After an extremely fancy animation, Github will log you in:

31. Touch the hamburger button and enter "termux-x11" in the search box:

32. Touch the first result:

33. Touch the "last successful build" link:

34. Touch the bold text next to the first green checkmark from the top down:

35. Scroll to the bottom of the page and touch the bold text reading "termux-x11" under "Artifacts"

36. Touch the file from downloads:

37. Choose to open with "My Files" (not "Termux"):

38. Select All and touch "UNZIP":

39. Touch the `app-debug.apk`:

40. Open with "Package installer" (not "Termux"):

41. You might see a warning very similar to the one covered in steps 5-7. If you trust Termux:X11, repeat that process.

42. Install the `termux-x11.deb` with this command:

```bash
dpkg -i /storage/emulated/0/Download/termux-x11/termux-x11.deb 
```

43. Install dependencies for everything that comes next. This will take a long time:
```bash
pkg install -y x11-repo
pkg install -y clang lld binutils-is-llvm cmake autoconf automake libtool '*ndk*' make python git libandroid-shmem 'vulkan*' ninja llvm bison flex libx11 xorgproto libdrm libpixman libxfixes libjpeg-turbo xtrans libxxf86vm xorg-xrandr xorg-font-util xorg-util-macros libxfont2 libxkbfile libpciaccess xcb-util-renderutil xcb-util-image xcb-util-keysyms xcb-util-wm xorg-xkbcomp xkeyboard-config libxdamage libxinerama sdl2 glew xfce4 pulseaudio
pip install meson mako
```

44. Clone [this](https://github.com/termux/termux-packages) repository and apply some changes I made to it. There is a chance a few of these changes might be upstreamed, so if the patch fails, it could mean upstream is deciding to officially support part of this guide, and I will hopefully revise this quickly.

```bash
git clone https://github.com/termux/termux-packages.git
cd termux-packages
curl https://clbin.com/4gLW2 | git apply -v
```

45. Verify installation of base dependencies:

```bash
./scripts/setup-termux.sh
```

46. **At this step, it's time to remember whether you have a Class A or Class B device. The contents of this step vary depending on which one you have.** Class B devices are less likely to work correctly, and **their patch used here will eventually stop working, assuming it even works for you now** (upstream support for them has been dropped). Class A devices have a much more optimistic future. **Choose only one at a time**:

- **Class A** devices:

```bash
curl https://clbin.com/eCrmH > packages/mesa/mesa-termux-zink.patch
```

- **Class B** devices:

```bash
curl https://clbin.com/IYvs1 > packages/mesa/mesa-termux-zink-revert-extension-requirements.patch
```

47. Build and install the custom `mesa`. This will take a long time:

```bash
./build-package.sh -I -f mesa
dpkg -i output/mesa_*
```

48. Build and install the custom `xwayland`. This will take some time:

```bash
./build-package.sh -I -f xwayland
dpkg -i output/
```

49. Clone this repository and place your `baserom.us.z64` in it. If you don't already have a `baserom.us.z64`, [here's the guide to obtain one](https://github.com/sanni/cartreader/wiki/What-to-order):

```bash
git clone https://github.com/robertkirkman/sm64ex-coop.git
cd sm64ex-coop
cp /storage/emulated/0/baserom.us.z64 .
```

50. Build this `sm64ex-coop` fork. This will take a while:

```bash
EXTERNAL_DATA=1 make -j$(nproc)
```

51. Launch Termux:X11 using the command provided by its companion package. You might need to grant permissions it requests:

```bash
termux-x11 &
```

52. Wait until you see a black screen, then launch XFCE once and wait until you can see the white mouse, then close it by pushing **Ctrl -> C**. This generates a configuration file which I suggest modifying in the next step:

```bash
env DISPLAY=:0 xfce4-session
```

53. Set XFCE's window borders to a slightly larger size so you can more easily move or resize the `sm64ex-coop` window on a high DPI screen:

```bash
sed -i 's/Default/Default-xhdpi/' ~/.config/xfce4/xfconf/xfce-per
channel-xml/xfwm4.xml
```

54. To quit Termux:X11, open the Notification Bar and look for a Termux:X11 notification with a tiny arrow next to it, then touch the arrow and touch "Exit". Unfortunately, to me it looks like the arrow does not exist on Android 8, so if you can't find it you might have to choose "FORCE STOP" on Termux:X11 in Android Settings (Android 10 pictured below):

55. In the picture above, you can also see a "Show Hacker's Keyboard" notification. **You will need that to enter your server address and port, or just your port if hosting, into `sm64ex-coop`**. To get it, set Hacker's Keyboard as your active touch keyboard and enable the notification in its settings.

56. To launch `sm64ex-coop`, use the script in this repository, or manually tweak and execute its commands:
> With Zink, performance can be unpredictable and scale differently from what you might expect. The primary bottleneck is that every frame is copied many times after it leaves the GPU to get it onto the Xwayland screen. This means that higher resolution lowers performance, but you can use more intensive graphics settings at the same resolution without losing performance, unlike what you would expect with a rasterization bottleneck.

```bash
cd
sm64ex-coop/launch-sm64ex-coop.sh
```