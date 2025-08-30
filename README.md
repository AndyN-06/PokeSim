# 🎮 Pokémon Adventure (C++ Simulation)

## 📖 Overview
Pokémon Adventure is a **C++ simulation game** inspired by the Pokémon universe.  
It models a small world where **Trainers** can move across a grid, battle in **Gyms**, heal at **Centers**, and encounter **Wild Pokémon**.  
The game is entirely **text-based** and played via typed commands.

---

## 🛠 Features
- **Object-Oriented Design** with core classes:
  - `GameObject` – Base class for all world objects
  - `Trainer` – Player characters (move, battle, recover)
  - `PokemonCenter` – Provides healing potions
  - `PokemonGym` – Hosts battles for experience
  - `WildPokemon` – Roam the world and interact with trainers
  - `Building` – Abstract base for gyms/centers
  - `Model` – Tracks world state and active objects
  - `View` – Renders the map in ASCII
- **Command System**:
  - `m <trainer_id> <x> <y>` → Move trainer to coordinates
  - `c <trainer_id> <center_id>` → Move trainer to a Pokémon Center
  - `g <trainer_id> <gym_id>` → Move trainer to a Pokémon Gym
  - `s <trainer_id>` → Stop trainer’s movement
  - `p <trainer_id> <num_potions>` → Recover trainer’s Pokémon health
  - `b <trainer_id> <num_battles>` → Battle in a Pokémon Gym
  - `a` → Advance one tick (time step)
  - `r` → Run until the next significant event
  - `n <type> <id> <x> <y>` → Create new object  
    (`c` = Center, `g` = Gym, `t` = Trainer)
  - `q` → Quit the game
- **Game Loop**: Every tick updates trainers, gyms, centers, and Pokémon
- **Win/Loss Conditions**:
  - ✅ Win: All gyms are defeated
  - ❌ Lose: All trainers faint

---

## 📂 Project Structure
├── main.cpp # Entry point / game loop
├── Model.cpp/.h # Manages world state
├── GameObject.cpp/.h # Base class for all objects
├── Trainer.cpp/.h # Trainer logic
├── PokemonCenter.cpp/.h
├── PokemonGym.cpp/.h
├── WildPokemon.cpp/.h
├── Building.cpp/.h
├── View.cpp/.h # ASCII grid visualization
├── GameCommand.cpp/.h # Command handling
├── Point2D.cpp/.h # 2D point representation
├── Vector2D.cpp/.h # 2D vector math
├── Input_Handling.h # Exception handling class
└── makefile.txt # Build instructions

---

## ⚡ Installation & Build
### Prerequisites
- C++11 (or newer) compiler: `g++`, `clang++`, or MSVC
- `make`

### Build
```bash
make        # builds the main game (PA3)
make clean  # removes binaries and object files
```

### Run
```bash
./PA3
```

### Example Gameplay
```bash
Enter command: m 1 5 5
Moving George Lopez to (5, 5)

Enter command: g 1 2
Moving George Lopez to gym 2

Enter command: b 1 3
George Lopez is battling
** George Lopez completed 3 battle(s)! **
** George Lopez gained 6 experience! **
```

### Sample Map Output

The View class renders the world as an ASCII grid:

20  .  .  .  .  C1 .  .  .  .  .  
18  .  .  .  .  .  .  .  .  .  .  
16  .  .  .  .  .  .  .  .  .  .  
14  .  .  .  .  .  W1 .  .  .  .  
12  .  .  .  .  .  .  .  .  .  .  
10  .  .  .  .  .  .  .  .  .  .  
 8  .  .  .  .  .  .  .  .  .  .  
 6  .  .  .  .  .  .  .  .  .  .  
 4  .  .  .  .  .  .  .  .  .  .  
 2  T1 .  .  .  .  G1 .  .  .  .  
 0  .  .  .  .  .  .  .  .  .  .  
    0  2  4  6  8 10 12 14 16 18
T1 = Trainer 1
C1 = Pokémon Center 1
G1 = Pokémon Gym 1
W1 = Wild Pokémon
