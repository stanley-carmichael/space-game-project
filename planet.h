#ifndef LOST_IN_SPACE_PLANET
#define LOST_IN_SPACE_PLANET

#include "splashkit.h"
#include <vector>
// #include "player.h"

using namespace std;
using std::vector;

#define PLANET_SPEED 0.5
#define ASTEROID_SPEED 10
#define PLANET_ROTATE_SPEED 100
#define SCREEN_BORDER 100

/**
 * Different options for the kind of planet.
 * Adjusts the image used.
 */
enum planet_type
{
    MERCURY,
    VENUS,
    PLUTO,
    MARS,
    JUPITER,
    SATURN,
    NEPTUNE,
    URANUS,
    EARTH
};

/**
 * The planet data keeps track of all of the information related to the planet.
 *
 * @field   planet_sprite    used to track position and movement of the planet.
 * @field   type            Current type of planet
 * @field  asteroid_sprite used to track postion and movement of asteroids.
 */
struct planet_data
{
    sprite planet_sprite;
    planet_type type;
    sprite asteroid_sprite;
};

bitmap planet_bitmap(planet_type type);

/**
 * Creates a new planet in the centre of the screen with the default planet.
 *
 * @returns     The new planet data
 */
planet_data new_planet(double x, double y);

void draw_planet(const planet_data &planet_to_draw);

void update_planet(planet_data &planet_to_update);

planet_data new_asteroid(double x, double y);

void update_asteroid(planet_data &asteroid_to_update);

void draw_asteroid(planet_data &asteroid_to_draw);

bool check_collision(sprite s1, sprite s2);

// void killer_asteroid( player_data &player, planet_data &asteroid);

// bool check_collisions(const planet_data &planet_sprite, const player_data &player_sprite);

#endif