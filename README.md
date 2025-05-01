# **CANOGA - C++ IMPLEMENTATION**

**PROJECT:** **P1 CANOGA**  
**AUTHOR:** **LUCAS MARETZO**  
**DATE:** **MARCH 2025**  

---

## **DESCRIPTION**

**This is a C++ implementation of the dice game Canoga, built using modern object-oriented programming (OOP) principles. The game features turn-based play between a human player and an AI-controlled computer player. Gameplay includes dice rolling, covering/uncovering squares, round-based scoring, and a handicap system carried across a tournament structure.**

---

## **OBJECT-ORIENTED DESIGN**

**The design of this project is centered around inheritance, polymorphism, and composition, which allows for clean, scalable, and reusable game logic.**

---

### **INHERITANCE**

**The base class Player provides shared functionality for both Human and Computer players. These two classes inherit from Player and override methods specific to their role.**

- **Player**: **Defines core AI logic such as square management and movement.**
- **Human**: **Inherits from Player, overrides decideMove() to handle user input.**
- **Computer**: **Inherits from Player, overrides decideMove() to use AI heuristics.**

---

### **POLYMORPHISM**

**The use of virtual functions like decideMove() allows the game loop to treat both players through a shared Player* interface. At runtime, the appropriate method is dispatched depending on whether the object is a Human or a Computer.**

**Example:**

Player* p1 = new Human(...);
Player* p2 = new Computer(...);

p1->decideMove(); // Calls Human::decideMove()
p2->decideMove(); // Calls Computer::decideMove()

---
**This design allows flexible and clean control flow without hardcoding logic for each player type.**

---

### **COMPOSITION**

**The Tournament class manages the overall structure and contains:**

- **Two Player objects (Human and Computer)**
- **A Dice object (for rolling)**
- **A sequence of Round objects**

**Each Round alternates turns, references both players, and checks win conditions. The Turn class manages a single move and uses the Dice class internally.**

---

## **KEY CLASSES**

### **Player**
- **Base class for Human and Computer**
- **Stores the board (vector of square states), score, and turn flags**
- **Includes shared logic for covering/uncovering and generating move combinations**

### **Human**
- **Inherits from Player**
- **Prompts the user for input**
- **Validates moves based on dice roll and opponent state**
- **Provides AI hints by calling base logic**

### **Computer**
- **Inherits from Player**
- **Overrides decideMove() with a strategy algorithm**
- **Evaluates both cover and uncover options**
- **Provides natural-language explanations for moves**

### **Dice**
- **Manages dice rolling logic**
- **Supports both random and manual input modes**
- **Returns rolls as std::pair<int, int>**

### **Tournament**
- **Manages scorekeeping and round sequencing**
- **Applies handicap logic based on win scores**
- **Supports game saving and loading**

### **Round**
- **Alternates turns**
- **Enforces rules for skipping, win conditions, and valid moves**
- **Records round winner and outcome for the Tournament**

---

## **FEATURES**

- **Manual dice mode for testing or controlled gameplay**
- **AI decision-making with explanations**
- **Hint system for the human player**
- **Handicap system that carries through rounds**
- **Save/load functionality for resuming progress**
- **Support for 9, 10, or 11 square board sizes**

---

## **BUILD INSTRUCTIONS**

**1. Open the project in Visual Studio**
**2. Make sure main.cpp is the entry point**
**3. Build and run the project as a Console Application**

---

## **CODE STRUCTURE**

- **main.cpp: Entry point, manages Tournament setup and control flow**
- **Player.h / Player.cpp: Base class with shared logic**
- **Human.h / Human.cpp: Handles user interaction**
- **Computer.h / Computer.cpp: AI move selection**
- **Dice.h / Dice.cpp: Dice rolling logic**
- **Tournament.h / Tournament.cpp: Overall game controller**
- **Round.h / Round.cpp: Single round and turn logic**
- **InputValidator.h / InputValidator.cpp: (Deprecated) Helper for parsing y/n input**

---

## **NOTES**

- **.gitignore excludes Visual Studio project files like .vcxproj and .filters**
- **Manual dice mode lets you test edge cases and simulate specific scenarios**
- **Handicap is applied by summing the digits of the winner's score (e.g., 2 + 7 = square 9)**
- **Game can end via full cover of your own board or full uncover of your opponent's board**

---

## **OOP HIGHLIGHTS**

- **Encapsulation: All logic for dice, players, and turns is self-contained in dedicated classes**
- **Inheritance: Human and Computer are derived from Player, reusing shared behavior**
- **Polymorphism: Virtual methods like decideMove() allow runtime decision-making**
- **Composition: Tournament contains Round; Round contains Turn, Player, and Dice**

---

## **CREDITS**

**AUTHOR: LUCAS MARETZO**  
**TOTAL TIME SPENT: 128 HOURS**
