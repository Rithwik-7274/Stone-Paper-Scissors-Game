# Stone-Paper-Scissors Game

A command-line implementation of the classic Stone-Paper-Scissors game against a computer, featuring ASCII art displays for moves and a 'best-of' series format. Designed with a retro, typewriter-like visual aesthetic. 

![Initial prompts](images/image-1.png)       

![Main gameplay loop](images/gif.gif)  

![Win message](images/image-2.png)

> **IMPORTANT DISPLAY NOTE:** To ensure the ASCII art and game UI fit perfectly on your screen without wrapping, you may need to adjust your terminal's zoom level. Use `Ctrl` + `+` or `-` (Linux/Windows) or `Cmd` + `+` or `-` (macOS) to scale the content properly.

## Installation

### Method 1: Arch Linux (via AUR)
If you are on Arch Linux, the game is available on the Arch User Repository. You can install it using your favorite AUR helper (such as `yay` or `paru`):
```bash
yay -S stone-paper-scissors
```

### Method 2: Linux, MacOS and WSL (via Homebrew)
The easiest way to install the game on macOS or other Linux distributions is using Homebrew: 
```shell
brew tap Rithwik-7274/stone-paper-scissors
brew install stone-paper-scissors
```

### Method 3: Build from Source
If you prefer to compile the game manually, follow these steps:

1. **Install Dependencies -**
Ensure you have gcc and the figlet utility installed.
    - **Arch Linux:** `sudo pacman -S gcc figlet`
    - **Debian/Ubuntu:** `sudo apt-get install gcc figlet`
    - **Fedora/RHEL/CentOS:** `sudo dnf install gcc figlet`
    - **macOS:** `xcode-select --install` and `brew install figlet`

2. **Clone and Compile -**
    ```shell
    git clone https://github.com/Rithwik-7274/Stone-Paper-Scissors-Game
    cd Stone-Paper-Scissors-Game
    make
    ```

## How to Play

1.  **Run the executable:**  If installed via -  
    - AUR/Homebrew, simply type `stone-paper-scissors` anywhere in your terminal.  
    - If compiled from source, run `./Stone-Paper-Scissors` in the Stone-Paper-Scissors-Game directory.

2.  **Enter your player name:**
    The game will prompt you to enter your player name.

3.  **Choose 'Best-of' series:**
    You'll then be asked to enter a **positive odd** integer for the 'Best-of' series (e.g., 3 for best of 3, 5 for best of 5).

4.  **Make your choice:**
    For each round, you'll be prompted to enter "Stone", "Paper", or "Scissors". Type your choice(Inputs are case-insensitive) and press Enter. The game will display the moves with ASCII art and update the scores.

5.  **Test your luck:**
    The game continues until you or the computer reaches the required number of wins for the 'best-of' series. The final result will be displayed using `figlet`.

## Project Structure 

* `Stone-Paper-Scissors.c`: The main source file containing all game logic, ASCII art definitions, and function implementations.
* `Doxyfile`: The configuration file for Doxygen, used to generate API documentation.
* `README.md`: This file.
* `LICENSE`: Contains the license used for the project.
* `Images/`: Contains visuals used in README.md
* `Makefile`: Contains make instructions.

## Doxygen Documentation

This project's code is thoroughly documented using Doxygen. You can generate and view the API documentation yourself:

1.  **Ensure Doxygen is installed -**
    * **Arch Linux:** `sudo pacman -S doxygen graphviz`
    * **Debian/Ubuntu:** `sudo apt install doxygen graphviz`
    * **Fedora/RHEL/CentOS:** `sudo dnf install doxygen graphviz`
    * **macOS (Homebrew):** `brew install doxygen graphviz` 

2.  **Clone and navigate to the project directory and run Doxygen -**
    ```shell
    git clone https://github.com/Rithwik-7274/Stone-Paper-Scissors-Game
    cd Stone-Paper-Scissors-Game
    doxygen
    ```

3.  **View the documentation:**
    Open `./docs/html/index.html`.

## Credits

Images were obtained from the sources below and converted to ascii art using [jp2a](https://github.com/cslarsen/jp2a).

* **Stone:** https://www.rawpixel.com/image/6791655
* **Scissors:** <a href="https://www.flaticon.com/free-icons/scissor" title="scissor icons">Scissor icons created by Icongeek26 - Flaticon</a>
* **Paper:** https://icon-icons.com/icon/document-duplicate-page-paper/124766
* **VS icon:** https://openclipart.org/detail/349242/versus-pictogram

*Overall project assistance was provided by Gemini.*

## License

This project is licensed under the **GPL-3.0-or-later** license. See the `LICENSE` file for the full license text.

## Author

**Rithwik A. Agarwal**

