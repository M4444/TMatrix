# TMatrix
TMatrix is a program that simulates the digital rain from The Matrix.
It's focused on being the most accurate replica of the digital rain effect achievable on a typical terminal, while also being customizable and performant.

### Install on Arch Linux
Install [`tmatrix-git`](https://aur.archlinux.org/packages/tmatrix-git/) from
the AUR. For example, with an [AUR helper](https://wiki.archlinux.org/index.php/AUR_helpers)
such as [`yay`](https://aur.archlinux.org/packages/yay/):
```
yay -S tmatrix-git
```

### Install on Gentoo Linux
```
eselect repository enable bright
emerge --ask tmatrix
```

### Install on NixOS Linux
```
nix-env -f channel:nixpkgs-unstable -iA tmatrix
```

### Download and install on other GNU/Linux distributions
TMatrix uses the ncurses library.
To install the library on Ubuntu or Debian run:
```
sudo apt-get install libncurses5
```
Now that you have the required library you can install and run tmatrix:
```
wget -q https://github.com/M4444/TMatrix/releases/download/v1.1/installation.tar.gz
tar -zxvf installation.tar.gz
cd installation
sudo ./install.sh
```
To check if it installed correctly run:
```
tmatrix --version
```

#### Uninstall
```
sudo rm -f /usr/bin/tmatrix /usr/share/man/man6/tmatrix.6.gz
```
To check if anything was left behind you can run:
```
whereis tmatrix
```

### Build and install from source
#### Tools
This project uses C++17 so you'll need the latest tools in order you build it:
- [CMake 3.8+](https://cmake.org/download/)
- [GCC 7+](https://gcc.gnu.org/) or [Clang 5+](http://releases.llvm.org/)

#### Library:
- [ncurses](https://www.gnu.org/software/ncurses/)

#### Commands
After cloning the repository run:
```
cd tmatrix
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make -j8
sudo make install
```

### Options
TMatrix is very customizable.
You can change the starting title text, the color of the background and the characters, the speed, length and separations of the rain streaks.

For a full description of all the options run `man tmatrix` or `tmatrix --help`.

### Contributing
Suggestions, bug reports and patch submissions are all welcome.
You can create an [issue](../../issues), send a [pull requests](../../pulls) of just send an [email](mailto:mc.cm.mail@gmail.com).
For details see [CONTRIBUTING.md](../master/CONTRIBUTING.md).

### Author
Written and maintained by Miloš Stojanović \<[mc.cm.mail@gmail.com](mailto:mc.cm.mail@gmail.com)\>.

### Acknowledgments
Thanks to:
- [Infinisil](https://github.com/Infinisil) for creating a NixOS Linux package
- [filalex77](https://github.com/filalex77) for creating a Gentoo Linux package
- [eliasrg](https://github.com/eliasrg) for creating an Arch Linux package and clarifying the installation options on Arch Linux
- [Makefile-dot-in](https://github.com/Makefile-dot-in) for fixing a problem linking atomic on Android
- [sebpardo](https://github.com/sebpardo) for pointing out a typo in the man page

### License
TMatrix is licensed under the `GPL-2.0-only` - see the [LICENSE](../master/LICENSE) file for details.

### How it looks:
![](assets/img/TMatrix.png?raw=true)
![](assets/img/TMatrix.gif?raw=true)
