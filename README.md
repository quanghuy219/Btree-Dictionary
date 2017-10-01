# Btree-Dictionary
Dictionary program utilizing b-tree structure 
## Build

Install ncurses library for Linux

Ubuntu: 
sudo apt-get install libncurses5-dev

https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

- Run `init_lib_btree.sh` to compile btree library
- Build :
```
make clean
make data && ./btfile 		//render data file dict.dat, soundExTree.dat
make
```
- Run `./main` 
