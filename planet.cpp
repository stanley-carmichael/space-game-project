#include "planet.h"
#include "splashkit.h"
#include "player.h"

// /**
//  * The ship bitmap function converts a ship kind into a
//  * bitmap that can be used.
//  *
//  * Not exposed by the header.
//  *
//  * @param kind  The kind of ship you want the bitmap of
//  * @return      The bitmap matching this ship kind
//  */
bitmap planet_bitmap(planet_type type)
{
    switch (type)
    {
    case MERCURY:
        return bitmap_named("mercury");
    case VENUS:
        return bitmap_named("venus");
    case PLUTO:
        return bitmap_named("pluto");
    case MARS:
        return bitmap_named("mars");
    case JUPITER:
        return bitmap_named("jupiter");
    case SATURN:
        return bitmap_named("saturn");
    case URANUS:
        return bitmap_named("uranus");
    case NEPTUNE:
        return bitmap_named("neptune");
    default:
        return bitmap_named("earth");
    }
}

planet_data new_planet(double x, double y)
{
    planet_data result;
    result.type = static_cast<planet_type>(rnd(9));

    bitmap default_bitmap = planet_bitmap(result.type);

    result.planet_sprite = create_sprite(default_bitmap);

    // Position planet at x y location.
    sprite_set_x(result.planet_sprite, x);
    sprite_set_y(result.planet_sprite, y);

    return result;
}

void draw_planet(const planet_data &planet_to_draw)
{
    draw_sprite(planet_to_draw.planet_sprite);
}

void update_planet(planet_data &planet_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(planet_to_update.planet_sprite);

    sprite_set_dx(planet_to_update.planet_sprite, PLANET_SPEED);
}

// create a new asteroid (pluto)
planet_data new_asteroid(double x, double y)
{
    planet_data result;
    result.type = (PLUTO);

    bitmap default_bitmap = planet_bitmap(result.type);

    result.asteroid_sprite = create_sprite(default_bitmap);

    // Position planet at x y location.
    sprite_set_x(result.asteroid_sprite, x);
    sprite_set_y(result.asteroid_sprite, y);

    return result;
}

void update_asteroid(planet_data &asteroid_to_update)
{
    update_sprite(asteroid_to_update.asteroid_sprite);

    sprite_set_dx(asteroid_to_update.asteroid_sprite, ASTEROID_SPEED);
}

void draw_asteroid(planet_data &asteroid_to_draw)
{
    draw_sprite(asteroid_to_draw.asteroid_sprite);
}

// to check if a collision had been made with the player and deduct score

// void killer_asteroid( player_data &player, planet_data &asteroid)
// {


//     if( sprite_collision((player.player_sprite), (asteroid.asteroid_sprite)) )
//     {
//         player.health -1;
//         asteroid = new_asteroid(rnd(10,50),rnd(50,100));
//         // draw_planet(planet_sprite);
//     }


// }
