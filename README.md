# Custom 2D Game Engine - Smurfs Adventure

> A complete 2D game engine built from scratch in C++ using SDL2, featuring Entity-Component System architecture, physics simulation, and advanced animation systems

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-3776AB?style=flat&logo=sdl&logoColor=white)

## 🎯 Overview

A fully custom 2D game engine developed without pre-built game frameworks, implementing professional game development patterns and systems. The engine powers a Smurfs-themed adventure game with grid-based movement, dynamic enemies, collectibles, and multi-level progression.

**Built for**: Advanced C++ Programming Course | 2023  
**Constraint**: No commercial game engines allowed (Unity, Unreal, Godot, etc.)  
**Solution**: Built a complete engine from scratch with 60+ modular components

## ✨ Engine Features

### Core Engine Systems
- **Entity-Component System (ECS)**: Composition-based architecture for flexible game object management
- **State Machine**: Menu → Play → Pause state transitions with proper context preservation
- **Game Loop**: Fixed timestep update loop with delta time management
- **Object Factory**: Dynamic object creation and lifecycle management
- **Resource Manager**: Texture caching and memory-efficient asset loading

### Graphics & Rendering
- **Sprite Rendering**: Hardware-accelerated 2D sprite rendering with SDL2
- **Animation System**: 
  - Sequential frame animation
  - Sprite sheet animation
  - Weather effects (rain, clouds)
- **Tilemap Rendering**: Multi-layer tilemap system with Tiled map editor integration
- **Camera System**: Smooth camera following with viewport management
- **UI Framework**: Custom widget system (buttons, panels, sliders, menus)

### Physics & Collision
- **Collision Detection**: AABB collision detection with CollisionMgr
- **Rigid Body Physics**: Velocity, acceleration, friction simulation
- **Collision Response**: Proper physics response for character-object interactions

### Gameplay Systems
- **Multiple Character Types**: Smurf, Warrior, Player entities with unique behaviors
- **Enemy AI**: Spider and Bzz Fly enemies with basic AI patterns
- **Item System**: 
  - Red Potion (Smurf-exclusive health boost)
  - Blue Potion (AOE healing)
  - Berry (universal health boost)
- **Level Progression**: Easy, Medium, Hard difficulty levels
- **Health System**: Character health management with boost mechanics

### Audio
- **SDL_mixer Integration**: Background music and sound effects
- **Sound Manager**: Event-based audio triggering
- **Music State Management**: Context-aware music switching (menu, gameplay, pause)

### Input & Controls
- **Input Abstraction Layer**: Platform-independent input handling
- **Keyboard & Mouse Support**: WASD/Arrow keys + mouse UI interaction
- **Event System**: SDL event processing with custom game events

## 🏗️ Architecture

### Entity-Component System

```
IObject (Interface)
    ↓
GameObject (Base)
    ↓
    ├── Entity (Dynamic Objects)
    │   ├── Player
    │   ├── Warrior
    │   ├── Smurf
    │   └── Enemy
    └── StaticObject (Non-moving)
```

**Components:**
- `Transform`: Position, rotation, scale
- `RigidBody`: Physics properties (velocity, mass, friction)
- `Collider`: Collision volumes (AABB)
- `Animation`: Animation state and sprite data

### State Management

```
StateMgr (State Machine Manager)
    ↓
GameState (Interface)
    ↓
    ├── Menu (Main menu, options, about)
    ├── Play (Active gameplay)
    └── Pause (Paused state)
```

### System Architecture

```
Engine (Core Loop)
    ↓
GameEngine (Game-specific logic)
    ↓
    ├── Input System
    ├── Collision Manager
    ├── Animation System
    ├── Render System
    ├── Physics System
    └── Audio System
```

## 📁 Project Structure

```
SDL2-Game-Engine/
├── Core Engine
│   ├── Engine.cpp/hpp              # Main engine loop
│   ├── GameEngine.cpp/hpp          # Game-specific engine
│   ├── StateMgr.cpp/hpp            # State machine
│   ├── GameManager.cpp/hpp         # High-level game logic
│   └── Timer.cpp/hpp               # Delta time, frame timing
│
├── Entity System
│   ├── IObject.hpp                 # Object interface
│   ├── GameObject.hpp              # Base game object
│   ├── Entity.cpp/hpp              # Entity base class
│   ├── Player.cpp/hpp              # Player entity
│   ├── Warrior.cpp/hpp             # Warrior character
│   ├── Smurf.cpp/hpp              # Smurf character
│   ├── Enemy.cpp/hpp               # Enemy base class
│   └── StaticObject.hpp            # Static objects
│
├── Component System
│   ├── Transform.hpp               # Position/rotation/scale
│   ├── RigidBody.hpp              # Physics component
│   ├── Collider.hpp               # Collision component
│   └── Animation.hpp              # Animation component
│
├── Physics & Collision
│   ├── CollisionMgr.cpp/hpp       # Collision detection
│   ├── RigidBody.hpp              # Physics simulation
│   └── Vector2D.hpp               # 2D vector math
│
├── Animation System
│   ├── Animation.hpp               # Animation interface
│   ├── SeqAnimation.hpp           # Sequential animation
│   ├── SpriteAnimation.cpp/hpp    # Sprite sheet animation
│   └── AnimationRain.cpp/hpp      # Weather effects
│
├── Rendering
│   ├── Camera.cpp/hpp             # Camera/viewport
│   ├── TextureMgr.cpp/hpp         # Texture management
│   ├── Background.cpp/hpp         # Background rendering
│   └── Layer.hpp                  # Rendering layers
│
├── Level System
│   ├── GameMap.hpp                # Map container
│   ├── TileMap.hpp                # Tilemap rendering
│   ├── TileLayer.hpp              # Layer management
│   └── Parser.cpp/hpp             # XML level parsing
│
├── UI System
│   ├── Menu.cpp/hpp               # Menu state
│   ├── Pause.cpp/hpp              # Pause menu
│   ├── Widget.hpp                 # Widget interface
│   ├── Button.cpp/hpp             # Button widget
│   ├── ButtonMenu.cpp/hpp         # Menu buttons
│   ├── Panel.hpp                  # UI panels
│   ├── Slider.cpp/hpp             # Slider widget
│   └── Message.cpp/h              # Message system
│
├── Input & Audio
│   ├── Input.cpp/hpp              # Input handling
│   └── SoundEffect.cpp/hpp        # Audio management
│
├── Utilities
│   ├── Vector2D.hpp               # Vector math
│   ├── ObjectFactory.cpp/hpp      # Factory pattern
│   ├── TinyXML (integration)      # XML parsing
│   └── Cloud.hpp, RainDrop.cpp    # Effects
│
└── Main
    └── main.cpp                    # Entry point
```

## 🔧 Technical Implementation

### 1. Entity-Component System (ECS)

The engine uses composition over inheritance for flexible entity design:

```cpp
class IObject {
public:
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Clean() = 0;
};

class GameObject : public IObject {
protected:
    Transform* transform;
    RigidBody* rigidBody;
    Collider* collider;
    Animation* animation;
};
```

**Benefits:**
- Add/remove components at runtime
- Reusable component logic
- Memory-efficient (only allocate needed components)

### 2. Object Factory Pattern

Dynamic object creation from level data:

```cpp
class ObjectFactory {
public:
    static GameObject* CreateObject(std::string type, Properties* props);
    static void RegisterType(std::string type, std::function<GameObject*()> creator);
};

// Usage in level loading:
GameObject* obj = ObjectFactory::CreateObject("Player", properties);
```

### 3. Collision Detection

Broad-phase and narrow-phase collision:

```cpp
class CollisionMgr {
public:
    void CheckCollisions();
    bool AABBCollision(Collider* a, Collider* b);
    void ResolveCollision(GameObject* a, GameObject* b);
};
```

### 4. State Machine

Clean game flow management:

```cpp
class StateMgr {
private:
    std::vector<GameState*> states;
    GameState* currentState;
public:
    void PushState(GameState* state);
    void PopState();
    void ChangeState(GameState* state);
};
```

### 5. Tilemap Integration

Loads levels from Tiled map editor XML:

```cpp
class Parser {
public:
    TileMap* ParseMap(std::string mapFile);
    TileLayer* ParseLayer(TiXmlElement* layerElement);
};
```

## 🎮 Gameplay Features

### Character System
- **Smurfs**: Primary playable characters with unique abilities
- **Warriors**: Alternative character class with different stats
- **Grid-based Movement**: Navigate -10 to 10 coordinate grid (easy mode)
- **Character States**: Idle, walking, damaged animations

### Enemy Types
- **Spiders**: Ground-based enemies with patrol patterns
- **Bzz Flies**: Flying enemies with different movement

### Item Mechanics
- **Red Potion**: Smurf-exclusive health restoration (amplified berry effect)
- **Blue Potion**: Area-of-effect healing for all creatures in forest
- **Berry**: Universal health boost for any character

### Level Design
- **Easy**: -10 to 10 coordinate range, basic enemies
- **Medium**: Expanded range, increased enemy density
- **Hard**: Maximum difficulty, complex enemy patterns

## 🛠️ Technologies Used

- **Language**: C++11/14
- **Graphics**: SDL2
- **Audio**: SDL2_mixer
- **Font Rendering**: SDL2_ttf
- **XML Parsing**: TinyXML
- **Level Editor**: Tiled Map Editor
- **Build System**: CMake (assumed)

## 💡 Design Patterns Implemented

1. **Entity-Component System**: Composition over inheritance
2. **State Pattern**: Game state management (Menu, Play, Pause)
3. **Factory Pattern**: Dynamic object creation (ObjectFactory)
4. **Singleton Pattern**: Resource managers (TextureMgr, Input)
5. **Observer Pattern**: Collision event system
6. **Strategy Pattern**: Different animation types
7. **Object Pool**: Particle system for rain/effects

## 🚀 Key Technical Achievements

### 1. Custom Game Loop
```cpp
void Engine::Run() {
    while(running) {
        float dt = Timer::GetDeltaTime();
        Input::Update();
        StateMgr::GetInstance()->Update(dt);
        CollisionMgr::GetInstance()->CheckCollisions();
        StateMgr::GetInstance()->Render();
    }
}
```

### 2. Camera Following
Smooth camera tracking with viewport bounds:
```cpp
void Camera::Update(float dt) {
    target = player->GetPosition();
    position = Lerp(position, target, FOLLOW_SPEED * dt);
    ClampToMapBounds();
}
```

### 3. Sprite Animation
Frame-based animation with timing:
```cpp
void SpriteAnimation::Update(float dt) {
    frameTimer += dt;
    if(frameTimer >= frameDelay) {
        currentFrame = (currentFrame + 1) % totalFrames;
        frameTimer = 0;
    }
}
```

## 🧠 Technical Challenges Overcome

### 1. **"Wait, We Need an Engine?"**
**Challenge**: Realized mid-development that game systems needed unifying architecture  
**Solution**: Refactored codebase to implement proper engine architecture with state management and system coordination

**Lessons Learned**:
- Plan architecture before implementation
- Recognize when ad-hoc code needs structure
- Value of design patterns in large codebases

### 2. **System Integration**
**Challenge**: Linking 60+ modules without circular dependencies  
**Solution**: Proper forward declarations, interface segregation, and manager classes

### 3. **Resource Management**
**Challenge**: Loading same textures multiple times causing memory bloat  
**Solution**: Implemented TextureMgr singleton with reference counting

### 4. **Collision Performance**
**Challenge**: O(n²) collision checks causing lag with many objects  
**Solution**: Spatial partitioning and early rejection using AABBs

## 📚 Learning Outcomes

This project demonstrates proficiency in:
- ✅ **Advanced C++**: Classes, inheritance, polymorphism, templates
- ✅ **Software Architecture**: ECS, state machines, design patterns
- ✅ **Game Programming**: Rendering pipelines, game loops, physics
- ✅ **Graphics Programming**: SDL2, sprite rendering, camera systems
- ✅ **Memory Management**: Resource caching, object pooling
- ✅ **Data Structures**: Spatial partitioning, scene graphs
- ✅ **File I/O**: XML parsing, resource loading
- ✅ **Mathematics**: Vector math, transforms, collision geometry
- ✅ **System Design**: Modular architecture, 60+ coordinated components

## 🎓 Academic Context

**Course Requirement**: Build a 2D game without using commercial engines  
**Approach**: Rather than create a simple game, built a complete reusable engine  
**Team Structure**: Group of 3 students, each building independent engine implementation  
**Collaboration Method**: Shared architecture discussions, unique feature additions per member

**Result**: Understanding of how commercial game engines (Unity, Unreal, Godot) work under the hood

## 🔮 Potential Enhancements

- [ ] Scripting system (Lua/Python integration)
- [ ] Advanced pathfinding (A* algorithm for enemy AI)
- [ ] Particle system for VFX
- [ ] Save/load game state
- [ ] Networking for multiplayer
- [ ] Advanced collision shapes (circles, polygons)
- [ ] Physics engine upgrade (Box2D integration)
- [ ] Animation state machine
- [ ] Asset pipeline tooling



## 📝 Technical Notes

### Why Build an Engine from Scratch?

Building a game engine teaches fundamental concepts that frameworks abstract away:
- **Memory Management**: How textures, objects, and resources are managed
- **Rendering Pipelines**: How sprites get from disk to screen
- **State Management**: How games transition between menus, gameplay, and pause
- **Physics Simulation**: How objects move and collide in game space
- **Event Systems**: How input propagates through game systems
- **Architecture**: How to organize thousands of lines of interdependent code

**Commercial engines (Unity, Godot) are built on these exact principles.**

---

**Keywords**: C++, SDL2, Game Engine, Entity-Component System, Game Development, 2D Graphics, Physics Engine, Animation System, State Machine, Design Patterns, Software Architecture
