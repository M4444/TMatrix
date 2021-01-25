# TMatrix

[![\[Latest GitHub release\]](https://img.shields.io/github/v/release/M4444/TMatrix)](https://github.com/M4444/TMatrix/releases)
[![\[License\]](https://img.shields.io/badge/license-GPL--2.0--only-green)](https://github.com/M4444/TMatrix/blob/master/LICENSE)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/995dada1ec344743921cdd10fc118f3a)](https://www.codacy.com/manual/M4444/TMatrix?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=M4444/TMatrix&amp;utm_campaign=Badge_Grade)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/M4444/TMatrix.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/M4444/TMatrix/context:cpp)

TMatrix is a program that simulates the digital rain from The Matrix.
It's focused on being the most accurate replica of the digital rain effect achievable on a typical terminal, while also being customizable and performant.

## Installation

[![Packaging status](https://repology.org/badge/vertical-allrepos/tmatrix-m4444.svg)](https://repology.org/project/tmatrix-m4444/versions)

### Install on Arch Linux [![AUR votes](https://img.shields.io/aur/votes/tmatrix-git)](https://aur.archlinux.org/packages/tmatrix-git)

Install [`tmatrix-git`](https://aur.archlinux.org/packages/tmatrix-git/) from
the AUR. For example, with an [AUR helper](https://wiki.archlinux.org/index.php/AUR_helpers)
such as [`yay`](https://aur.archlinux.org/packages/yay/):
```shell
yay -S tmatrix-git
```

### Install on Gentoo Linux
```shell
eselect repository enable bright
emerge --ask tmatrix
```

### Install on any Nix system
```shell
nix-env -f '<nixpkgs>' -iA tmatrix
```

### Install on openSUSE Linux

The package can be installed from the community repo:
#### For openSUSE Tumbleweed
```shell
zypper addrepo https://download.opensuse.org/repositories/home:kosmonaut2000/openSUSE_Tumbleweed/home:kosmonaut2000.repo
zypper refresh
zypper install TMatrix
```
#### For openSUSE Leap 15.2
```shell
zypper addrepo https://download.opensuse.org/repositories/home:kosmonaut2000/openSUSE_Leap_15.2/home:kosmonaut2000.repo
zypper refresh
zypper install TMatrix
```

### Download and install on other GNU/Linux distributions
The prebuilt TMatrix uses **version 5** of the ncurses library.
To install the library on Ubuntu or Debian run:
```shell
sudo apt-get install libncurses5
```
Now that you have the required library you can install and run tmatrix:
```shell
wget -q https://github.com/M4444/TMatrix/releases/download/v1.3/installation.tar.gz
tar -zxvf installation.tar.gz
cd installation
sudo ./install.sh
```
To check if it installed correctly run:
```shell
tmatrix --version
```

#### Uninstall
```shell
sudo rm -f /usr/bin/tmatrix \
           /usr/share/man/man6/tmatrix.6.gz \
           /usr/share/bash-completion/completions/tmatrix \
           /usr/share/zsh/site-functions/_tmatrix
```
To check if anything was left behind you can run:
```shell
locate tmatrix
```

### Build and install from source
#### Tools
This project uses C++17 so you'll need the latest tools in order you build it:
- [CMake 3.8+](https://cmake.org/download/)
- [GCC 7+](https://gcc.gnu.org/) or [Clang 5+](http://releases.llvm.org/)

#### Library
- [ncurses](https://www.gnu.org/software/ncurses/)

#### Commands
```shell
git clone https://github.com/M4444/TMatrix.git
cd TMatrix
mkdir -p build && cd build
cmake ..
make -j8
sudo make install
```

## Info

### Options
TMatrix is very customizable.
You can change the starting title text, the color of the background and the characters, the speed, length and separations of the rain streaks.
During execution you can use `p` to pause and `q` to quit.

For a full description of all the options run `man tmatrix` or `tmatrix --help`.

### Contributing
Suggestions, bug reports and patch submissions are all welcome.
You can create an [issue](../../issues), send a [pull requests](../../pulls) of just send an [email](mailto:mc.cm.mail@gmail.com).
For details see [CONTRIBUTING.md](../master/CONTRIBUTING.md).

### Author
Written and maintained by Miloš Stojanović ([mc.cm.mail@gmail.com](mailto:mc.cm.mail@gmail.com)).

### Acknowledgments
Thanks to:
- [Infinisil](https://github.com/Infinisil) for creating a Nix package
- [filalex77](https://github.com/filalex77) for creating a Gentoo Linux package, adding bash, zsh and tcsh completions scripts and a .editorconfig file
- [eliasrg](https://github.com/eliasrg) for creating and maintaining the Arch Linux package, clarifying the installation options on Arch Linux, adding CMake install commands for the man page and helping in the creation of completions scripts
- [Makefile-dot-in](https://github.com/Makefile-dot-in) for fixing a problem linking atomic on Android
- [sebpardo](https://github.com/sebpardo) for pointing out a typo in the man page
- [fosspill](https://github.com/fosspill) for correcting the name of the required ncurses library
- [meskarune](https://github.com/meskarune) for the idea and helpful suggestions for creating the 'fade' and 'rainbow' options
- [taschenlampe](https://github.com/taschenlampe) for creating a openSUSE Linux package and reporting an issue with the install script

### License
TMatrix is licensed under the `GPL-2.0-only` - see the [LICENSE](../master/LICENSE) file for details.

### Donations
If you wish to send a donation you can do so here [![Liberapay](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/M4444/donate) or here [![PayPal](assets/img/PayPal.png?raw=true)](https://www.paypal.com/paypalme/4milos).

### How it looks
![](assets/img/TMatrix.png?raw=true)
![](assets/img/TMatrix.gif?raw=true)
