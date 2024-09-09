# Embedded Game Engine

This is a lightweight embedded game engine designed for a 32x64 RGB LED panel with a 3-bit color depth. It supports both simulation mode (on desktop) and deployment to STM32 devices.

## Screenshots

<div style="display: flex; flex-wrap: wrap; gap: 10px;">
    <img src="https://github.com/user-attachments/assets/997c176e-a0dc-4d0e-9787-f5e92fb56412" height="120" style="object-fit: cover;" alt="Doom game screenshot">
    <img src="https://github.com/user-attachments/assets/38b02370-b9d7-48ba-a98a-14dc18aad43a" height="120" style="object-fit: cover;" alt="3D rotating mesh screenshot">
    <img src="https://github.com/user-attachments/assets/16075061-7352-4673-be63-811db8bdfc1a" height="120" style="object-fit: cover;" alt="Sand simulation screenshot">
    <img src="https://github.com/user-attachments/assets/b3379a27-7117-458a-8727-d2d07badf9c0" height="120" style="object-fit: cover;" alt="Game of Life simulation screenshot">
    <img src="https://github.com/user-attachments/assets/9c5d3d7c-fa95-4512-83a1-740b2ae67b17" height="120" style="object-fit: cover;" alt="Rule 110 cellular automaton screenshot">
    <img src="https://github.com/user-attachments/assets/af0b7875-8fd0-4444-bfcd-36bed13c6394" height="120" style="object-fit: cover;" alt="Text rendering screenshot">
</div>

## Features
- Simple game loop (`on_ready()`, `on_update()`, `on_event()`)
- Simulated mode using raylib
- STM32 support
- Demos included:
  - **Doom**
  - **3D Rotating Mesh**
  - **Sand Simulation**
  - **Game of Life**
  - **Rule 110**
  - **Scrolling Text**
  - **Dino Game**

## Building

### Prerequisites
- CMake
- raylib (for simulation)
- GCC/Clang (for simulation)
- ARM toolchain (for STM32)

### Build with CMake

```bash
# Clone the repo
git clone https://github.com/hanion/embedded-engine.git
cd embedded-engine

# Build for simulation mode
mkdir build_sim && cd build_sim
cmake ../src/platform/sim
make

# Build for STM32
mkdir build_stm && cd build_stm
cmake ../src/platform/stm
make

```

## Running

**Sim Mode**: Run the executable created in `build_sim/`: `./ee-sim`

**STM Mode**: Flash the `ee-stm.elf` binary to the STM32 device using your preferred method (e.g., `stm32flash`).
To enable keyboard input transfer via UART, connect your STM32 device to your computer, then run: `./connect.py`

<br>

## Usage Guide

The engine provides a basic `Application` class, which you can derive from and implement the game logic through the following methods:

### `on_ready()`
Called once at the start.

### `on_update(double delta_time)`
Main update loop called every frame, where game logic is executed. This is also where you handle drawing to the buffer.

```cpp
void on_update(double delta_time) {
    Renderer::clear_back_buffer();
    // Update game state and draw here
    Renderer::draw_number(delta_time, 0, 0);
}
```

### `on_event(Event event)`
Handles input events like key presses and releases.

```cpp
void on_event(Event event) {
    if (event.type == Event::Type::Pressed) {
        if (event.keycode == 'a') {
            // Do something when 'a' is pressed
        }
    }
}
```

### To create your own application and make it run, follow these steps:

In your custom application’s `.cpp` file, you need to define the following function:

```cpp
Application* CreateApplication() {
    return new YourAppClass();
}
```

Remove `CreateApplication()` from `src/app/showcase_demos.cpp` if you’re replacing `ShowcaseDemos` with your own app.

<br>

## Renderer Features

In the on_update method, you can use the `Renderer` to draw various shapes, text, and meshes. Here are some useful functions:
```cpp

// Clear the buffer:
Renderer::clear_back_buffer();

// Set a pixel:
Renderer::set_pixel(int x, int y, const Color& color);

// Draw a line:
Renderer::draw_line(int x0, int y0, int x1, int y1, Color color);

// Draw a rectangle:
Renderer::draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color color);

// Draw a number:
Renderer::draw_number(int num, int x, int y);

// Draw text:
Renderer::draw_text(const char *text, int x, int y);

// Draw a mesh (3D rendering):
Renderer::draw_mesh(const Mesh& mesh, const Transform& transform, const Camera& camera);

```

