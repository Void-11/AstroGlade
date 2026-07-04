# AstroGlade 🚀

A feature-rich 2D space shooter game built with C++ using SFML and Box2D physics, featuring a custom game engine architecture.

![AstroGlade](assets/preview.png)

## 🎮 About the Game

AstroGlade is an intense space shooter where you pilot a spaceship through waves of enemies, collecting power-ups and battling challenging bosses. The game showcases modern C++ game development practices with a clean, modular architecture separating the engine from game logic.

### 🌟 Key Features

- **Fast-paced space combat** with smooth controls and responsive gameplay
- **Multiple enemy types** including Vanguards, Twin Blades, UFOs, Hexagons, and epic Bosses
- **Weapon system** with upgradeable shooters (Laser, Three-way, Frontal Wiper)
- **Power-up system** with health packs, weapon upgrades, and extra lives
- **Stage-based progression** with increasing difficulty
- **Visual effects** including explosions, particles, and dynamic backgrounds
- **HUD system** with health bars, score tracking, and life counters
- **Physics-based gameplay** using Box2D for collision detection and movement

## 🏗️ Architecture

The project is divided into two main components:

### AstroGladeEngine 🔧
A reusable 2D game engine providing core functionality:
- **Application Framework** - Window management, main game loop, event handling
- **World/Actor System** - Scene management and game object hierarchy  
- **Physics Integration** - Box2D integration with collision handling
- **Asset Management** - Texture and font loading with automatic cleanup
- **Widget System** - UI components (buttons, text, gauges, images)
- **Timer Management** - Scheduling system for delayed actions
- **VFX System** - Particle effects and visual enhancements
- **Game Stage System** - Level progression and game state management

### AstroGlade Game 🎯
Game-specific implementation using the engine:
- **Spaceship Hierarchy** - Player and enemy ship implementations
- **Weapon System** - Multiple weapon types with upgrade mechanics
- **Enemy AI** - Various enemy behaviors and attack patterns
- **Level Design** - Main menu, gameplay levels, and boss stages
- **HUD Implementation** - Game UI with health, score, and controls
- **Player Management** - Lives, scoring, and progression systems

## 🔧 Technical Details

### Dependencies
- **SFML 2.6.1** - Graphics, audio, input, and window management
- **Box2D 2.4.1** - 2D physics simulation
- **CMake 3.27.7+** - Build system
- **Visual Studio 2022** - C++ compiler (Windows)
- **C++14 Standard** - Modern C++ features

### Design Patterns
- **Actor-Based Object Model** - Game objects derive from `Actor`, with lightweight components for shared behavior such as health
- **Template Programming** - Type-safe generic containers and smart pointers
- **Resource Management** - RAII principles with smart pointers
- **Observer Pattern** - Delegates for event handling
- **Factory Pattern** - Dynamic object creation for enemies and rewards
- **State Machine** - Game stage management and progression

## 🚀 Building the Project

### Prerequisites
- Windows 10/11
- Visual Studio 2022 Build Tools
- CMake 4.x
- Git

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd AstroGlade
   ```

2. **Configure the project:**
   ```bash
   cmake -B build -S . -G "Visual Studio 17 2022" -A x64
   ```

3. **Build the project:**
   ```bash
   cmake --build build --config Release --parallel
   ```

4. **Run the game:**
   ```bash
   cd build/AstroGlade/Release
   ./AstroGlade.exe
   ```

### Build Outputs
- `AstroGlade.exe` - Main game executable
- `AstroGladeEngine.lib` - Static engine library
- Required DLLs (SFML, Box2D) are automatically copied to output directory
- Assets folder with game textures, sounds, and fonts

## 🎮 Controls

- **WASD / Arrow Keys** - Move spaceship
- **Spacebar** - Shoot
- **Mouse** - Navigate menus
- **ESC** - Pause/Menu

## 🎯 Gameplay Systems

### Weapon Types
1. **Laser Shooter** - Standard single-shot weapon
2. **Three-Way Shooter** - Fires three projectiles in a spread pattern  
3. **Frontal Wiper** - Wide-angle area denial weapon

### Enemy Types
1. **Vanguard** - Basic enemy with simple movement patterns
2. **Twin Blade** - Agile fighter with twin projectiles
3. **UFO** - Unpredictable movement with energy shots
4. **Hexagon** - Geometric enemy with unique attack patterns
5. **Boss** - Multi-stage boss with multiple weapon systems

### Power-Ups
- **Health Pack** - Restores player health
- **Weapon Upgrades** - Enhances current weapon or provides new ones
- **Extra Life** - Grants additional lives
- **Score Multipliers** - Increases point values

## 🏢 Project Structure

```
AstroGlade/
├── AstroGladeEngine/          # Reusable game engine
│   ├── include/
│   │   ├── framework/         # Core engine systems
│   │   ├── widgets/          # UI components
│   │   ├── VFX/             # Visual effects
│   │   └── gameplay/         # Game mechanics
│   └── src/                 # Engine implementation
├── AstroGlade/              # Game-specific code
│   ├── include/
│   │   ├── gameFramework/   # Game application
│   │   ├── spaceship/       # Ship implementations  
│   │   ├── weapon/          # Weapon system
│   │   ├── enemy/           # Enemy types and AI
│   │   ├── player/          # Player management
│   │   ├── Level/           # Game levels
│   │   └── widgets/         # Game UI
│   ├── src/                 # Game implementation
│   └── assets/              # Game resources
├── build/                   # Generated build files
├── CMakeLists.txt          # Main build configuration
└── README.md               # This file
```

## 📚 Documentation

- [AstroGladeEngine.md](AstroGladeEngine.md) - Detailed engine documentation for developers
- Code is extensively commented with clear class hierarchies
- Header files provide comprehensive API documentation

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Coding Standards
- Follow existing code style and naming conventions
- Use modern C++ features appropriately
- Maintain clean separation between engine and game code
- Add comments for complex algorithms and public APIs
- Test changes thoroughly before submitting

## 📝 License

This project is open source. Feel free to use, modify, and distribute according to your needs.

## 🙏 Acknowledgments

- **SFML Team** - For the excellent multimedia library
- **Box2D** - For robust 2D physics simulation  
- **Game assets** - Space Shooter Redux pack for visual resources
- **Audio assets** - CC0 sounds and music listed in `AstroGlade/assets/Audio/AUDIO_SOURCES.md`
- **Modern C++** - For powerful language features enabling clean architecture

## 📞 Support

If you encounter any issues or have questions:
- Check the documentation in `AstroGladeEngine.md`
- Review the source code for implementation details
- Open an issue on the repository

---

*Made with ❤️ using modern C++ and game development best practices*
