
# README ncurses-tetris

This is a simple weekend hacking project I did to learn a little more about C and the ncurses library. Results is a fully playable tetris game with a game loop and a scoring system.

# Building

ncurses-tetris depends on ncurses to for building. So before running `make`, execute:

```
git clone https://github.com/poutipie/ncurses-tetris
cd ncurses-tetris/3rdp-pkgs

tar zxvf ncurses.tar.gz  # unzip and untar the archive
cd ncurses-6.3           # cd to the directory
./configure              # configure
make                     # make it
sudo make install        # install it
```

Once ncurses is installed, the project should build with make:
```
cd ncurses-tetris
make
```
The binary will appear in a folder called `build/`, so run the program with:
```
.\build\tetris
```

Enjoy!
