#include "player.h"
#include "splashkit.h"
#include "planet.h"

/**
 * The ship bitmap function converts a ship kind into a
 * bitmap that can be used.
 *
 * Not exposed by the header.
 *
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    default:
        return bitmap_named("pegasi");
    }
}

player_data new_player()
{
    player_data result;
    bitmap default_bitmap = ship_bitmap(AQUARII);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // Default to layer 0 = Aquarii so hide others
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);

    result.kind = AQUARII;


    // Position in the centre of the initial screen

    float sprWidth = sprite_width(result.player_sprite);
    float sprHeight = sprite_height(result.player_sprite);

    float sprOFFsetX = sprWidth/ 2;
    float sprOFFsetY = sprHeight/ 2;

    sprite_set_x(result.player_sprite, 400 - sprOFFsetX );
    sprite_set_y(result.player_sprite, 400  - sprOFFsetY );

    return result;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player_to_update.player_sprite);

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Test if the player is outside the area and move the camera
    // the player will appear to stay still and everything else
    // will appear to move :)

    // Test top/bottom of screen
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

/**
 * Switch the ship kind - will adjust which layer is hidden/shown
 */
void player_switch_to_ship(player_data &player, ship_kind target)
{
    // only do this if there is a change
    if (player.kind != target)
    {
        // show then hide layers
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.kind));

        // remember what is currently shown
        player.kind = target;
    }
}

void handle_input(player_data &player)
{
    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_to_ship(player, AQUARII);
    if (key_typed(NUM_2_KEY))
        player_switch_to_ship(player, GLIESE);
    if (key_typed(NUM_3_KEY))
        player_switch_to_ship(player, PEGASI);

    // Handle movement - rotating left/right and moving forward/back
    float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases
    if (key_typed(DOWN_KEY))
        sprite_set_dx(player.player_sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(player.player_sprite, dx + PLAYER_SPEED);
}

void draw_hud(const player_data &player,  const  planet_data &planet)
{
    fill_rectangle(COLOR_WHITE, 0, 0, 300, 40, option_to_screen());
    draw_text("SCORE: " + to_string(player.score), COLOR_BLACK, 0, 0, option_to_screen());
    draw_text("Health: " + to_string(player.health),COLOR_BLACK, 0,10, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(player.player_sprite)), COLOR_BLACK, 0, 20, option_to_screen());
    draw_text("DISTANCE TO PLANET: " + to_string(point_point_distance(center_point(player.player_sprite),center_point(planet.planet_sprite))), COLOR_BLACK,0,30, option_to_screen());
}

/**
 * @brief function to return a score if the ship and the plannet collide.
 * player_data and plannet_data required to determine if a collision has happened
 * generates a new plannet after collision
 *
 */
void player_score( player_data &player_sprite, planet_data &planet_sprite)
{


    if( sprite_collision((player_sprite.player_sprite), (planet_sprite.planet_sprite)) )
    {
        player_sprite.score ++;
        planet_sprite = new_planet(rnd(10,500),rnd(50,1000));
        // draw_planet(planet_sprite);
    }


}



