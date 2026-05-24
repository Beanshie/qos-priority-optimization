# QoS Priority Management Optimization in Networks - Binary Heap and Unordered Array 🚀

An research project developed as part of university coursework, aiming to analyze the performance of data structures used to manage network traffic priorities (Quality of Service). The project compares a **Binary Heap (Max-Heap)** against a **Naive Unordered Array**, analyzing their behavior under extreme workloads (up to 200,000 packets) and simulated network congestion (DDoS attacks / Burst scenario).

The full theoretical and mathematical analysis, along with key findings, can be found in the `QoS Project Report [PL].pdf` file attached to this repository.

---

## 📂 Project Structure
* `/src` - C++ source files (simulation engine, structure implementations).
* `/include` - Header files.
* `/scripts` - Python scripts for generating log-log and linear charts.
* `/results` - Target directory for generated logs (.csv) and plots (.png).
* `CMakeLists.txt` - CMake build system configuration file.

---

## 🛠️ Environment Setup from Scratch

To run this project on a clean system (e.g., Windows), you need to install a few tools. The project utilizes **C++20** and **Python 3** for data visualization.

### Step 1: Required Software
1. **Visual Studio Code** - Download and install the code editor from [code.visualstudio.com](https://code.visualstudio.com/).
2. **C++ Compiler (GCC/MinGW or MSVC)** - On Windows, the easiest way is to install *Build Tools for Visual Studio* or the *MSYS2* environment (with the GCC package).
3. **CMake** - The build system tool. Download it from [cmake.org](https://cmake.org/download/).
4. **Python 3** - Download it from [python.org](https://www.python.org/downloads/). During installation, **make sure to check the box "Add python.exe to PATH"**!

### Step 2: Required VS Code Extensions
After launching VS Code, go to the *Extensions* tab (or press `Ctrl+Shift+X`) and install:
* **C/C++** (by Microsoft)
* **CMake Tools** (by Microsoft)
* **Python** (by Microsoft)

### Step 3: Python Libraries
Open the terminal (in VS Code press `Ctrl + \``) and install the necessary libraries for plotting the data:
```bash
pip install pandas matplotlib