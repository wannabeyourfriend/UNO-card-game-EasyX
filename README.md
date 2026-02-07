# UNO Card Game (EasyX)

A C++ implementation of the classic UNO card game using the EasyX graphics library.

## Overview

This project is an imitation of the famous UNO card game, developed using C++ and the EasyX graphics library for Windows. It features a graphical interface that recreates the classic UNO gameplay experience.

![Gameplay Screenshot 1](https://github.com/user-attachments/assets/cee4ff2d-0be1-4eab-b21e-46c86ecd130b)
![Gameplay Screenshot 2](https://github.com/user-attachments/assets/c9d52348-c7f9-485a-b5d3-06dea2255a83)
![Gameplay Screenshot 3](https://github.com/user-attachments/assets/90869539-50ed-45a6-a87a-496fe138e57d)
![Gameplay Screenshot 4](https://github.com/user-attachments/assets/bd0b6707-8482-4f09-ba49-327334d1b889)

## Features

- **Classic UNO Gameplay**: Implements standard UNO rules including:
  - Number cards (0-9) in four colors (Red, Yellow, Green, Blue)
  - Action cards (Skip, Reverse, Draw Two)
  - Wild cards (Wild, Wild Draw Four)
- **Graphical Interface**: Visual card game interface using EasyX
- **Sound Effects**: Background music and sound effects
- **AI Opponents**: Play against computer-controlled opponents

## Requirements

- **Operating System**: Windows (EasyX is Windows-specific)
- **Compiler**: Visual Studio (MSVC) or MinGW
- **Graphics Library**: [EasyX Graphics Library](https://easyx.cn/) (Windows only)

## Installation

1. Install [EasyX Graphics Library](https://easyx.cn/)
2. Clone this repository:
   ```bash
   git clone https://github.com/wannabeyourfriend/UNO-card-game-EasyX.git
   ```
3. Open the project in Visual Studio or compile with your preferred C++ compiler
4. Ensure EasyX library is properly linked

## Usage

1. Compile the project using Visual Studio or g++
2. Run the executable
3. Follow on-screen instructions to play

### Controls
- Mouse click to select and play cards
- Follow the game's visual prompts

## Project Structure

```
UNO-card-game-EasyX/
├── Basicfunction/       # Basic UNO game logic implementation
├── src/                 # Main source code
│   ├── main.cpp        # Entry point
│   ├── uno_logic.cpp/h # Core game logic
│   ├── visualize.cpp/h # Graphics and UI rendering
│   └── music.cpp       # Sound effects
├── resource/           # Game resources (images, sounds)
├── test/              # Test files
└── report.pdf         # Project report (Chinese)
```

## Game Rules

- Each player starts with 7 cards
- Match the top card of the discard pile by color, number, or symbol
- Action cards have special effects:
  - **Skip**: Next player loses their turn
  - **Reverse**: Changes direction of play
  - **Draw Two**: Next player draws 2 cards and loses turn
  - **Wild**: Can be played on any card, choose the color
  - **Wild Draw Four**: Next player draws 4 cards and loses turn
- Call "UNO" when you have one card left
- First player to empty their hand wins

## Development

This project was developed as a course assignment implementing classic UNO gameplay with a graphical interface.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available for educational purposes.

## Acknowledgments

- EasyX Graphics Library for the graphics framework
- Classic UNO game by Mattel
