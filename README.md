Sample project: how to use SD card with raspberry pico-sdk

## Requirements:

- Linux or Windows 10 PC with [WSL (Windows Subsystem Linux)](https://learn.microsoft.com/pt-br/windows/wsl/install) - Ubuntu is recommended;
- [Visual Studio Code](https://code.visualstudio.com/download) with the [ms-vscode.cpptools-extension-pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) and [ms-vscode-remote.vscode-remote-extensionpack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack) extensions (both from Microsoft).

## B.O.M. (Bill Of Material):

- RaspberryPi Pico;
- MicroSD to SD card adapter (for easy soldering);
- MicroSD card;
- Some nice wires (30 AWG recommended);
- 2 x 10K resistors (for pull-up);
- 1 x 10uF capacitor (for decoupling);

## Wiring:

Soon...

## Getting started:

- Start a Linux terminal (on windows, just open the `command prompt` and type `wsl`);
- Install the build system, running the following command on terminal:

```
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential libstdc++-arm-none-eabi-newlib
```

- Download the repository with it's dependencies:

```
git clone --recurse-submodules --shallow-submodules https://github.com/juliannojungle/pico-sdk-sdcard.git
```

- Once vscode is open, click on the 'no kit selected' on status bar to select `GCC arm-none-eabi` build kit, then click on `Build` (right next to it);

`*.uf2` file will be written at `build` directory. Just copy it to the raspberry pico's usb drive.
