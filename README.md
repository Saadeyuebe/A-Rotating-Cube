🛠 How to Install C++ Compiler (MinGW)
Download MinGW:

Go to: https://www.mingw-w64.org/

Click "Downloads", and select the installer for your system.

Run the Installer:

Choose architecture: x86_64

Threads: posix

Exception: seh

Build revision: latest

Add to PATH:

After installation, go to the bin folder (e.g., C:\Program Files\mingw-w64\...\bin)

Copy the path, then:

Open Start Menu → Search “Environment Variables”

Edit the Path variable and add the copied path

Verify Installation:
Open Command Prompt and run:

g++ --version

You should see your compiler version 
