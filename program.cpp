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
    asteroid = new_asteroid(100,300);
    // set player score to 0
    player.score = 0;
    // set player health to 100
    player.health = 100;

//  create variables to check collision between the asteroid and player
    sprite s1 = player.player_sprite;
    sprite s2 = asteroid.asteroid_sprite;

    while ( not quit_requested() )
    // ends the game if the players health is 0
    {   if(player.health <= 0)
        {
        clear_screen(COLOR_BLACK);
        draw_text("GAME OVER!! " ,COLOR_RED, 350, 300, option_to_screen());
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

            if(check_collision(s1, s2))
            {
                player.health -= 1  ;
                asteroid = new_asteroid(100, 300);
            }

            // if(point_point_distance(center_point(player.player_sprite),center_point(planet.asteroid_sprite)) > 750)
            // {
            //     asteroid = new_asteroid(100, 300);
            // }

            // check to see if player has found planet and update there score.
            player_score(player, planet);

            // Redraw everything
            clear_screen(COLOR_BLACK);

            draw_hud(player, planet);

            // as well as the player who can move
            draw_player(player);
            draw_planet(planet);
            draw_asteroid(asteroid);

            refresh_screen(60);
        }
    }

    return 0;
}