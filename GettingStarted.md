# Getting started
To create new application you have to include `engine/EntryPoint.h` and implement `Engine::CreateGame()` function.

You can inherit from `Game` class and implement your own behavior.

```
class App : public Game {
};

Game* Engine::CreateGame() {
    return new App;
}
```

## Architecture
The engine is separated into 4 modules - Engine, Renderer, OpenGl, and Helpers. You can see
all the classes and namespaces in [this diagram](architecture.pdf).

### Engine
The basic entity in the game is `GameObject` which implements the ECS pattern.
A game object contains components that define its behavior and attributes. Components can be 
`Mesh`, `SpritesheetTex` and `Transform`.

You shouldn't create the game objects directly instead you should use the `GameObjectFactory`.

All objects are stored in pieces of terrain called `Chunk`. The chunks are stored in `Scene`.
Chunks in the scene are automatically generated and cleared based on render distance.

The engine also includes class `Random` which contains static noise methods and implementation of 
Perlin and Simplex noise. You are encouraged to set a game seed to the `Random` class which 
influences all other noise functions.

If you are interested in L-system generation you can you the prepared `LSystems` namespace.
This allows you to load L-systems from a file, and parse them into `LSystem` object which
stores the grammar and constants. You can later use the L-system to generate game objects.

### Renderer
Namespace `Renderer` is tied to OpenGL implementation. You can use classes `Shader` and `Texture2D`
to represent the OpenGL concepts with useful helper methods like setting uniforms or recompiling
shader with different macros.

`SceneRenderer` uses light and shadow shader to render the scene but you can of course 
change them to your implementation. Shadows are implemented with a simple map or cascaded shadow
mapping which results in better performance and shadow quality.

Objects are by default rendered with `CubeRenderer` which can render closed or any part of a cube. 
Eg. cube without bottom and top.

To render a non-cube object you can specify your own geometry in `Mesh` class (becomes part of a game
object's component) by creating vertices and defining their order with indices. Vertex contains
position, normal, and texture coordinates.

### Helpers
Namespace `Helpers` provides functions for transforming objects (matrices, vectors, ...) 
into strings and common mathematical operations. 

## Terrain generator
You are free to change any part of the terrain generator to your liking.
You can use the default texture pack or your own. Consider using a sprite sheet as it 
offers better performance. 

You can access all the textures in an enum `BlockType` in `Terrain.h`. To create your own 
sprite sheet and appropriate enum class use python scrip `make_spritesheet.py` in the textures folder.
This script will merge all the images into one, generate enum based on image names and create a get
function that returns the image position on the sprite sheet.
