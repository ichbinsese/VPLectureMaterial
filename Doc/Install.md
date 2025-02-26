# Installation

## Ubuntu VirtualBox Installation
Download the Ubuntu 24.10 ISO Image
https://ubuntu.com/download/desktop

Create a VirtualBox VM for Linux and install Ubuntu with default packages. The VM should have at least 4GB of RAM

Update the package database

    $ sudo apt-get update

## Download Kali Linux VM
If you don't want to install a Linux distribution by your own, just download a ready-to-use Kali Linux VM
https://www.kali.org/get-kali/#kali-virtual-machines

## Prerequisites
The following tools should be installed on the Linux system used for the Lecture examples

- NeoVim
- XZ Utils
- Git
- GCC and build essentials (incl. Make)
- OpenJDK
- CMake
- Python
- Curl
- WGet

### Install Prerequisites

    $ sudo apt-get install neovim xz-utils git gcc build-essential
    $ sudo apt-get install openjdk-21-jdk cmake python3 curl wget


## Tools

### ARM GNU Toolchain

    $ cd ~
    $ mkdir Tools

    $ wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz

    $ tar xvfJ arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz

    $ mv arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi arm-gnu-toolchain

To run the GNU ARM tools from any directory, the `PATH` environment variable must be extended. For this, open the file `.bash_profile` in NeoVim (or any other editor) and add the following line

    export PATH=$PATH:~/Tools/arm-gnu-toolchain/bin

After saving the file, it must be reloaded to apply the changes and make them available

    $ source .bash_profile

### QEmu

    $ sudo apt-get install qemu-system

### OpenOCD

    $ sudo apt-get install openocd

### Eclipse

Download Eclipse for C/C++

    $ cd ~/Tools

    $ wget https://eclipse.mirror.liteserver.nl/technology/epp/downloads/release/2024-12/R/eclipse-cpp-2024-12-R-linux-gtk-x86_64.tar.gz

    $ tar xvfz eclipse-cpp-2024-12-R-linux-gtk-x86_64.tar.gz
