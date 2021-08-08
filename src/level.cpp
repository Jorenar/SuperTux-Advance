#include "level.hpp"

#include "globals.hpp"
#include "tile_manager.hpp"
#include "tile_renderer.hpp"

Level::Level(uint16_t* raw, const uint16_t* pal, Tileset* tileset) :
    colmap{ reinterpret_cast<uint8_t*>(raw+1) },
    interactive{ raw + 1 + raw[0]/2 }, // `raw[0]/2` bc `sizeof uint16_t` == `2 * sizeof uint8_t`
    background{ ptrToNextTileMap(interactive) },
    skybox{ ptrToNextTileMap(background) }
{
    tile_manager->set_tileset(tileset);
    tile_renderer->set_tilemap(1, &interactive);
    tile_renderer->set_tilemap(2, &background);
    tile_renderer->set_tilemap(3, &skybox);
    tile_renderer->set_palette(pal);
    tile_renderer->done();
}
