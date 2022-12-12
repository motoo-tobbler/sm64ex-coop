#!/data/data/com.termux/files/usr/bin/bash
cd build/us_pc
termux-x11 &
sleep 5
env DISPLAY=:0 xfce4-session &
DISPLAY=:0 GALLIUM_DRIVER=zink MESA_NO_ERROR=1 ZINK_DESCRIPTORS=lazy ./sm64.us.f3dex2e