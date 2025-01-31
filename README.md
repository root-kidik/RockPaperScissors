# Rock Paper Scissors

## Build

### Linux (Ubuntu 24.04 LTS)

```
sudo apt update
sudo apt install libx11-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxau-dev libxaw7-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxres-dev libxss-dev libxv-dev libxxf86vm-dev libxcb-glx0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-dri2-0-dev libxcb-dri3-dev libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev libxcb-util-dev libxcb-util-dev

python3 -m venv env
source env/bin/activate
pip3 install conan

cat <<EOL > ~/.conan2/profiles/clang_debug
[settings]
os=Linux
arch=x86_64
compiler=clang
compiler.version=18
compiler.libcxx=libc++
build_type=Debug
compiler.cppstd=20

[buildenv]
CC=/usr/bin/clang
CXX=/usr/bin/clang++
EOL

cat <<EOL > ~/.conan2/profiles/clang_release
[settings]
os=Linux
arch=x86_64
compiler=clang
compiler.version=18
compiler.libcxx=libc++
build_type=Release
compiler.cppstd=20

[buildenv]
CC=/usr/bin/clang
CXX=/usr/bin/clang++
EOL

conan install . --build=missing --profile:all=clang_debug
conan install . --build=missing --profile:all=clang_release
```
