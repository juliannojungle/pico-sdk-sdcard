Sample project: how to use SD card with raspberry pico-sdk

## Requirements: :heavy_check_mark:

- Linux or Windows 10 PC with [WSL (Windows Subsystem Linux)](https://learn.microsoft.com/pt-br/windows/wsl/install) - Ubuntu is recommended;
- [Visual Studio Code](https://code.visualstudio.com/download) with the following Microsoft extensions:
  - [ms-vscode.cpptools-extension-pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack);
  - [ms-vscode-remote.vscode-remote-extensionpack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack);
  - [ms-vscode.vscode-serial-monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor).

## B.O.M. (Bill Of Materials): :shopping_cart:

- [RaspberryPi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/);
- MicroSD to SD card adapter (for easy soldering);
- MicroSD card;
- Some nice wires (30 AWG recommended);
- 2 x 10K resistors (for pull-up);
- 1 x 10uF capacitor (for decoupling);

## Wiring: :electric_plug:

Soon...

## Development :space_invader:

- Start a Linux terminal (on windows, just open the `command prompt` and type `wsl`);
- [Install the build system](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf), running the following command on terminal:

```
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential libstdc++-arm-none-eabi-newlib
```

- Download the repository with it's dependencies:

```
git clone --recurse-submodules --shallow-submodules https://github.com/juliannojungle/pico-sdk-sdcard.git
```

- Open the project folder in vscode, click on the 'no kit selected' on status bar, select `GCC arm-none-eabi` build kit, then click on `Build` (right next to it);

`*.uf2` file will be written at `build` directory. Just copy it to the raspberry pico's usb drive.

---
<sup>[@juliannojungle](https://github.com/juliannojungle), 2023</sup>
