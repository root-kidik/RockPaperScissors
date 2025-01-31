# Rock Paper Scissors

## Build

### Linux (Ubuntu 24.04 LTS)

```
sudo apt update
sudo apt install libx11-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxau-dev libxaw7-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxres-dev libxss-dev libxv-dev libxxf86vm-dev libxcb-glx0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-dri2-0-dev libxcb-dri3-dev libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev libxcb-util-dev libxcb-util-dev

sudo apt install python3-virtualenv
python3 -m venv env
source env/bin/activate
pip3 install conan

cp profiles/linux.gcc.debug   ~/.conan2/profiles/
cp profiles/linux.gcc.release ~/.conan2/profiles/

conan install . --build=missing --profile:all=linux.gcc.debug
conan install . --build=missing --profile:all=linux.gcc.release
```

### Windows (Windows 11)

- git https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.2/Git-2.47.1.2-64-bit.exe
- visual studio https://visualstudio.microsoft.com/ru/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false
- python https://www.python.org/ftp/python/3.13.1/python-3.13.1-amd64.exe
- cmake https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi

- vscode https://code.visualstudio.com/download#
- расширения для vscode:
    - C/C++
    - CMake
    - CMake Tools

в powershell от имени администратора
Set-ExecutionPolicy RemoteSigned

python -m venv env
env/Scripts/activate

pip install conan

conan profile detect
conan install . --build=missing -s:a compiler.cppstd=17

В vscode включить
Cmake › Options: Status Bar Visibility -> visible

затем выбрать пресет и собрать