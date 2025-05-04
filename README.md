# 🌀 Double Pendulum Chaos Simulation

A visualization of 200 double pendulums with slightly different initial conditions, demonstrating chaotic behavior.

[![SFML](https://img.shields.io/badge/SFML-2.5.1-blue.svg)](https://www.sfml-dev.org/)

<img src="images/video.gif" alt="Double Pendulum Chaos Demonstration" width="400" height="400">

## Table of Contents
- [Dependencies](#-dependencies)
- [Installation](#-installation)
- [Usage](#-usage)
- [Configuration](#-configuration)
- [Controls](#-controls)
- [License](#-license)

## 📦 Dependencies
- SFML (Simple and Fast Multimedia Library)
- C++17 compiler
- Make build system

### Installing SFML
**Linux:**
```bash
sudo apt-get install libsfml-dev
``` 

## 🛠️ Installation
1. Clone the repository:
```bash
git clone https://github.com/yursds/double_pendulum_chaos.git
cd double_pendulum_chaos
``` 

2. Build the project:
```bash
make
``` 

## 🚀 Usage
Run the simulation:
```bash
./main
``` 

## ⚙️ Configuration
Modify simulation parameters in [`include/double_pendulum.h`](include/double_pendulum.h):
- Number of pendulums
- Initial angle ranges
- Physical properties (masses, lengths)
- Visual properties (colors, trail length)

## 🎮 Controls
| Key            | Action                          |
|----------------|---------------------------------|
| `SPACE`        | Start/Pause simulation         |
| `LEFT/RIGHT`   | Adjust first angle (±π/36)     |
| `UP/DOWN`      | Adjust second angle (±π/36)    |
| `R`            | Reset simulation               |
| `ESCAPE`       | Quit application               |
