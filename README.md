# FisheyOS (BIOS)
Some COOL OS i created i guess, where u can draw stuff. The idea is sorta basic:

If user presses WASD, the cursor (pointed out as text 0xB8000, no graphics mode cuz its too hard) moves based on the key 
yez, its open source
also u gotta hold enter if you want to draw stuff (yes, WITH the cursor lol)
and stop holding enter if you want to stop drawing stuff

its small asf, but heres how to run it

firstly, use WSL
I used ubuntu for it so i guess use it either
To install it, do as admin:
wsl --install Ubuntu
ANNND wait some moments
and just at the root, do
./build.sh
make sure you install stuff like qemu, gcc, nasm, and ld
after that qemu will appear and let you do stuff

yea thats it

(working on DOS rq and added some mini cmd prompt)
