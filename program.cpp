#include "splashkit.h"
#include "player.h"
#include "planet.h"
using namespace std;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}
// procedure dealing with asteroid collisiosn and health.
void asteroid_collision(player_data &player, planet_data &asteroid)
{
    //  create variables to check collision between the asteroid and player
    sprite s1 = player.player_sprite;
    sprite s2 = asteroid.asteroid_sprite[0];

    //check if there has been a collision between the player and asteroid. then dedeuct helath and spawn new asteroid.
    if(sprite_collision(s1, s2))
        {
            player.health -= 5  ;
            asteroid.asteroid_sprite.pop_back();
            asteroid = new_asteroid(rnd(-100,-10), rnd(0,600) );
        }

        if(point_point_distance(center_point(s1), center_point(s2)) > 1000  )
        {
            asteroid.asteroid_sprite.pop_back();
            asteroid = new_asteroid(rnd(-100,-10), rnd(0,600));
        }
}

/**
 * Entry point.
 *
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 600);
    load_resources();


    player_data player;
    player = new_player();
    planet_data planet;
    planet = new_planet(200,50);
    planet_data asteroid;
    asteroid = new_asteroid(rnd(-100,-10),300);
    // set player score to 0
    player.score = 0;
    // set player health to 100
    player.health = 100;




    while ( not quit_requested() )
    // ends the game if the players health is 0
    {   if(player.health <= 0)
        {
            clear_screen(COLOR_BLACK);
            draw_text("GAME OVER!! " ,COLOR_RED, 350, 300, option_to_screen());
            refresh_screen(60);
            delay(6000);
        }

        //Mission complete when player finds more than 10 planets.
        else if (player.planets_found.size() > 10)
        {
            clear_screen(COLOR_BLACK);
            draw_text("MISSION COMPLETE!! ",COLOR_WHITE_SMOKE, 350, 300, option_to_screen());
            refresh_screen(60);
            delay(6000);
        }
        else
        {
            // Handle input to adjust player movement
            process_events();
            handle_input(player);

            // Perform movement and update the camera
            update_player(player);
            update_planet(planet);
            update_asteroid(asteroid);

            //procedure dealing with asteroid collisions and health.
            asteroid_collision(player,asteroid);

            // check to see if player has found planet and update there score.
            player_score(player,planet);

            // Redraw everything
            clear_screen(COLOR_BLACK);

            draw_hud(player,planet);

            // as well as the player who can move
            draw_player(player);
            draw_planet(planet);
            draw_asteroid(asteroid);

            refresh_screen(60);
        }
    }

    return 0;
}