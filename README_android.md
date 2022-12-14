# How to play `sm64ex-coop` on Android

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

9. Open Termux and wait until the "installing bootstrap packages" message disappears. Then, the first thing you need to do is type `pkg update` and press Enter (or "Go" as some touch keyboards label it):

![image](https://user-images.githubusercontent.com/31490854/207103297-03620115-e5d3-46de-bc69-58c74dfabf4b.png)


10. When it is first installed, Termux frequently has outdated mirrors. If you see any errors like these (will have a red `E:`), then type `termux-change-repo` next, and press Enter. If you don't see any errors, skip to step 17:

![image](https://user-images.githubusercontent.com/31490854/207103444-c206ab3d-5245-4ca4-b392-7930e6db65d7.png)
![image](https://user-images.githubusercontent.com/31490854/207103521-8658e35f-8d7f-4b36-b416-7eda94bfa53a.png)


11. Press Enter again when you see this first screen:

![image](https://user-images.githubusercontent.com/31490854/207103623-82f57c13-c0c9-486b-b3bc-529ff13e4e3a.png)


12. At this screen, use the arrow keys _above_ your normal touch keyboard to navigate up and down, then press Space to select a _different_ mirror, then press Enter to confirm:

![image](https://user-images.githubusercontent.com/31490854/207103874-9ab3eed7-c2c5-47da-89df-1b9e14cc95da.png)


13. The red `E:` should be gone from the black screen with white text; if it's not, repeat steps 14-16 until it's gone. Then, type `pkg upgrade -y` and press Enter:

![image](https://user-images.githubusercontent.com/31490854/207104093-8037ed9f-207d-403b-bc28-262633f167a4.png)


14. You will see repeated messages like this, which end with "The default action is to keep your current version", followed by some letters. Press **Shift -> I -> Enter** every time you see this, because this is a new installation that doesn't contain any custom settings you created:

![image](https://user-images.githubusercontent.com/31490854/207104260-172db617-cc34-4699-a079-d8320ea6c055.png)


15. The `pkg upgrade` will take some time. After it has finished, you will see `~ $` again. These next few steps are aimed towards connecting a desktop or laptop with a large keyboard to your Android device so that you can type, copy, paste, and run the commands in the later steps more quickly. If you have or prefer to use only one device, then you can skip to step 26, and all of the later commands will work the same when typed directly into the Termux app. Type `pkg install openssh -y` and press Enter:

![image](https://user-images.githubusercontent.com/31490854/207104319-d51ab7f1-e1bd-4903-8d1e-117acb8aba9e.png)


16. When you can see `~ $` again, type `passwd` and press Enter. You should now type and confirm a new password that you can remember. This is the password you will type to connect from the other device. **`passwd` (and for later, `ssh` too) do not show the characters you type, so if you think you mistyped, you should try pressing backspace a lot of times and start over, before pressing Enter**:

![image](https://user-images.githubusercontent.com/31490854/207104403-2a6583aa-d54e-4e69-9652-f36dea53b0ec.png)
![image](https://user-images.githubusercontent.com/31490854/207104636-e8a4a0b8-8f7a-4f23-a11d-dc53f54d7937.png)



17. There are a few ways you can connect. If you want to connect over **Wi-Fi**, you just need to be connected to the same router on both devices, or if your Android device supports it you could enable "Mobile Hotspot" in Android settings and connect your other device to the resulting network. If you want to connect over **USB**, you can use either RNDIS or ADB protocol, and the connection might be less stuttery, but you will have to keep the Android device plugged into the other device. For RNDIS, you would need to enable "USB tethering" in Android settings, and for ADB, you would have to enable Android Developer Mode, enable USB Debugging, install [ADB Tools](https://developer.android.com/studio/command-line/adb) onto the other device, and run the `adb forward tcp:8022 tcp:8022` command on that device. **To keep this guide from being even longer, I will only cover the Wi-Fi connection here**.

18. Install the `ip` command with `pkg install iproute2 -y`, then type `ip a` and swipe down to scroll up slightly. You need to look for an IPv4 address of the form `X.X.X.X` located in between two instances of a string that may or may not be "`wlan0`". Unfortunately it can be a bit hard to find here, so if you can't find it, check that you are connected to Wi-Fi, and you should also be able to see it in Android Settings -> Connections -> Wi-Fi -> Gear icon near the connected SSID -> IP Address. This is the IP address you will type to connect from the other device (pictured is my local IP Address, yours is different):

![image](https://user-images.githubusercontent.com/31490854/207105158-fee645a1-e2fe-4dea-a4db-527e0b947202.png)


19. On the other device, open a terminal that has access to the `ssh` command. If the other device has Windows 10 or 11, MacOS or GNU/Linux, it is probably already installed and easily accessible by opening a PowerShell or XTerm window. If it has an older version of Windows, you can use [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) ([source code](https://git.tartarus.org/?p=simon/putty.git;a=tree)), which has different syntax but is compatible with OpenSSH servers and isn't too hard to figure out.

20. Type `sshd` on the Termux app, then on the other device, type `ssh -p 8022 X.X.X.X` where you replace "`X.X.X.X`" with the IP Address you found in step 22, then press Enter.

![image](https://user-images.githubusercontent.com/31490854/207105585-f5dfc528-cfce-4be9-b78b-72dd109ca913.png)


21. Type "`yes`" to confirm connecting to a new device, then type the password you chose in step 20, and press Enter. You should now see the Termux MOTD (welcome message) and `~ $`. From this point, commands for running in Termux will be placed in code blocks, so that Github gives them copy buttons for easily pasting into this window. Unfortunately, the button to paste into terminal varies wildly by client OS, but on Windows you can try right click.

22. Give software running as Termux's Android-assigned user permission to access `/storage/emulated/0`. A popup will appear; touch "ALLOW":

```bash
termux-setup-storage
```

![image](https://user-images.githubusercontent.com/31490854/207105668-f6b8f2c5-7c21-4cd3-999e-c7c3702674e7.png)

23. Install dependencies:

```bash
pkg install git wget make python getconf zip apksigner clang binutils aapt
cd platform/android/ && ./getkhrplatform.sh && ./getSDL.sh && cd ../..
```

24. Clone this repository and place your `baserom.us.z64` in it. If you don't already have a `baserom.us.z64`, [here's the guide to obtain one](https://github.com/sanni/cartreader/wiki/What-to-order):

```bash
git clone https://github.com/robertkirkman/sm64ex-coop.git
cd sm64ex-coop
cp /storage/emulated/0/baserom.us.z64 .
```

25. Build this `sm64ex-coop` fork. This will take a while. When it is finished, you can install the `.apk`:

> At the moment I see a lot of repeated "This app was built for an older version of Android and may not work properly" warnings when installing the `.apk`, and if you have any other Android `sm64ex` builds installed the installation might fail. Uninstall other builds first (after backing up your data), then accept all the warnings.

```bash
make -j$(nproc)
cp build/us_pc/sm64.us.apk /storage/emulated/0
```
