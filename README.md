🎴 SET Card Game

A C++ implementation of the classic SET card game, featuring object-oriented design patterns and memory management.

🎯 Game Overview

SET is a real-time card game where players compete to identify "SETs" of three cards. Each SET must satisfy the condition that for each of the four attributes (color, number, shape, filling), all three cards are either all the same or all different.

🏗️ Project Structure
```
SET_MY/
├── MySet.h              # Header file with class declarations
├── MySet.cpp            # Implementation of game logic
├── main.cpp             # Main game entry point
├── CMakeLists.txt       # Build configuration
└── README.md            # This file
```

🏛️ Class Architecture

Core Classes

• Carte: Represents a single card with 4 attributes

• Jeu: Manages all 81 cards (Singleton pattern)

• Pioche: Handles card drawing and deck management

• Plateau: Game board with dynamic card array

• Combinaison: Validates SET rules for 3 cards

• Jouer: Player information and scoring

• Controleur: Main game controller (Singleton pattern)

Key Design Patterns

• Singleton: Jeu::GetInstance(), Controleur::GetInstance()

• Iterator: Custom iterators for card collections

• Factory: Card creation through Jeu class

🎮 Features

Core Gameplay

• 81 Unique Cards: All possible combinations of 4 attributes

• Real-time SET Detection: Automatic validation of player selections

• Dynamic Card Distribution: Smart card dealing with SET availability checks

• Multi-player Support: Turn-based gameplay for multiple players

Technical Implementation

• Singleton Pattern: Jeu and Controleur classes ensure single instances

• Iterator Pattern: Custom iterators for card traversal

• Memory Management: Manual dynamic array management

• Exception Handling: Custom exception classes for error management

🃏 Card Attributes

Each card has four attributes with three possible values:

Attribute Values

Color 🔴 Rouge, 🟢 Vert, 🟣 Mauve

Number 1, 2, 3

Shape ⚪ Ovale, 🌊 Vague, ♦️ Losange

Filling ■ Plein, □ Vide, ▤ Hachure

🚀 How to Compile and Run

Prerequisites

• C++11 compatible compiler

• CMake (recommended) or direct compilation

Using CMake

mkdir build && cd build
cmake ..
make
./SET_Game


Direct Compilation

g++ -std=c++11 MySet.cpp main.cpp -o SET_Game
chcp 65001
./SET_Game


🎯 How to Play

1. Start the Game: Run the executable
2. Enter Player Count: Input the number of players
3. Player Names: Enter names for each player
4. Gameplay:
   • The game displays 12 cards on the table

   • Players take turns selecting 3 cards by their numbers

   • Enter 0 0 0 to exit the game

   • Valid SETs award points to the player

5. Winning: The player with the most SETs when the deck is empty wins!

Example Turn

```
=== Current Cards on Table ===
1.[rouge 1 vague hachure]   2.[vert 2 vague vide]   3.[vert 3 ovale plein]
4.[vert 1 vague vide]       5.[vert 3 ovale vide]    6.[vert 1 ovale hachure]
7.[rouge 1 vague plein]    8.[mauve 1 ovale vide]  9.[mauve 1 vague vide]
10.[mauve 3 ovale plein]   11.[mauve 1 ovale hachure] 12.[vert 2 losange plein]

Alice, please make your selection: (enter card numbers)
> 1 5 9
```

Enjoy playing SET! 🎴✨
