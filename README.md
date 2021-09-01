## Project

This project is an unfinished roguelike game. I wanted to learn to use different types of programming patterns such as as components, dependency injection and factories.
Initially I used [libtcod](https://github.com/libtcod/libtcod) for world/dungeon generation and learning more about coding a roguelike game. Afterwards I decided to code dungeon generator by myself and then I switched terminal to [BearLibTerminal](https://github.com/tommyettinger/BearLibTerminal). [BSP](https://en.wikipedia.org/wiki/Binary_space_partitioning) is used for dungeon generator. It's also a technique that I wrote my Bachelor of Science about.
Initially this project was written using Qt while also avoiding any dependencies to Qt libraries.

### Structure
* /components contain components for different actors/gameobjects that can be present but also the game menu components.
* /gameworld contain world generation, engine, factories and different behaviour components that actors/gameobjects can have (should be moved to components dir).
* /gameworld/object contain data for generating actors/gameobjects with object factory.