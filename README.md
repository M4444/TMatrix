# TMatrix
TMatrix is a program that simulates the digital rain from The Matrix.
It's focused on being the most accurate replica of the digital rain effect achievable on a typical terminal, while also being customizable and performant.

### Download and install
TMatrix uses the ncurses library.
To install it on Ubuntu or Debian run:
```
sudo apt-get install libncurses5-dev
```
Now that you have the required library you can install and run tmatrix:
```
wget -q https://github.com/M4444/TMatrix/releases/download/v1.0/installation.tar.gz
tar -zxvf installation.tar.gz
cd installation
sudo ./install.sh
```
To check if it installed correctly run:
```
tmatrix --version
```

### Build and install
#### Tools
This project uses C++17 so you'll need the latest tools in order you build it:
- [CMake 3.8+](https://cmake.org/download/)
- [GCC 7+](https://gcc.gnu.org/)

#### Library:
- [ncurses](https://www.gnu.org/software/ncurses/)

#### Commands
After cloning the repository run:
```
cd tmatrix
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=bin/ ..
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
- [Makefile-dot-in](https://github.com/Makefile-dot-in) for fixing a problem linking atomic on Android

### License
TMatrix is licensed under the `GPL-2.0-only` - see the [LICENSE](../master/LICENSE) file for details.

### How it looks:
![](assets/img/TMatrix.png?raw=true)
![](assets/img/TMatrix.gif?raw=true)
