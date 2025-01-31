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

cp profiles/linux.clang.debug   ~/.conan2/profiles/
cp profiles/linux.clang.release ~/.conan2/profiles/

conan install . --build=missing --profile:all=linux.clang.debug
conan install . --build=missing --profile:all=linux.clang.release
```

### Windows (Windows 11)

- download: https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi
- download: https://www.python.org/ftp/python/3.13.1/python-3.13.1-amd64.exe
- download: https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/LLVM-18.1.8-win64.exe

открыть консоль от имени администратора и вставить комманду
возможно версия компилятора будет отличаться, нужно обязательно вашу версию указать
```
setx PATH "%PATH%;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.41.34120\bin\Hostx64\x64" /M
```

```
pip install ninja

pip install virtualenv
python -m venv env
env/Scripts/activate
pip install conan

copy profiles\windows.msvc.debug ~\.conan2\profiles\
copy profiles\windows.msvc.release ~\.conan2\profiles\

conan install . --build=missing --profile:all=windows.msvc.debug
conan install . --build=missing --profile:all=windows.msvc.release
```