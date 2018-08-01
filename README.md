# Indie Studio - Bomberman

## Description
The goal of this Epitech project was to create a Bomberman from scratch with the help of the Irrlicht library.

## System requirements
### Linux
 - Lua v5.3
 - OpenGL
 - Irrlicht library v1.8.4
 - IrrKlang library v1.6

### Windows
 - Visual C++ Redist 2017

## Installation
### Linux (Ubuntu or Fedora)
Go to the "*[bomberman repository]/installer/linux*" folder and run :

    sudo ./configure

After the installation you need to go back to the root of the repository and go under the "*[bomberman repository]/build*" folder.

> Create the "*build*" folder if he doesn't exist already

To compile and play to the game you just need to write the following commands :

    make
    ./bomberman

And if you want to install it on your system, you need to write this one :

    sudo make install

### Windows
Go to the "*[bomberman repository]/installer/windows*" folder and double-click on :

    bomberman_setup.exe

> If you already have Visual C++ Redist 2017 installed on your computer just cancel when the setup ask you to repair or modify it

## Uninstall
### Linux

> Be careful ! Use only if you use "*sudo make install*" before.

Go to the "*[bomberman repository]/installer/linux*" folder and run :

    sudo ./uninstall

> This will only remove Irrlicht, IrrKlang and the game files. All dependencies like Lua or OpenGL will remain on your system.

### Windows
Use the classical way to uninstall an application.
Go to your apps settings, look for "*Bomberman version 1.0*", click on uninstall and follow the instructions.

> If you also want to remove the Visual C++ Redist do the same by looking for "*Microsoft Visual C++ 2017 Redistribuable*"

## Authors
 - Lucas Benkemoun - [Github](https://github.com/LeBenki)
 - Issam Mahssoume
 - Alexandre Babonneau - [Github](https://github.com/FWolowitz)
 - Simon Bineau
 - Baptiste Coudoulet - [Github](https://github.com/bc2606)
 - Jordan Bonaldi