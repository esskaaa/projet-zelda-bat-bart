#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
Vector2f movement(0.f, 0.f);
#include <map>;
using namespace std;
typedef Vector2f vec2;
typedef Vector2i vec2i;


namespace level {
    map<string, vec2i> tile_offsets = {
        { "convex_angle1", {0,0}},    //
        { "convex_angle2", {1,0}},    //

        { "convex_side1", {0,1}},     //
        { "convex_side2", {1,1}},     //

        { "convex_angle3", {0,2}},    //
        { "convex_angle4", {1,2}},    //


        { "forest_NW", {2,0}},        //
        { "forest_N", {3,0}},         //
        { "forest_NE", {4,0}},        //

        { "forest_W", {2,1}},         //
        { "forest_C", {3,1}},         //
        { "forest_E", {4,1}},         //

        { "forest_SW", {2,2}},        //
        { "forest_S", {3,2}},         //
        { "forest_SE", {4,2}},        //

        { "forest_S2", {0,5}},        //


        { "tree_big_1", {0,3}},       //
        { "tree_big_2", {1,3}},       //
        { "tree_big_3", {0,4}},       //
        { "tree_big_4", {1,4}},       //


        { "stump1", {2,3}},           //
        { "stump2", {2,4}},           //
        { "flowers", {3,3}},          //
        { "grass", {1,5}},            //

        { "ground", {4,6}},           //

        { "pool", {3,3}},             //
        { "river_corner_BL", {1,6}},  //
        { "river_corner_BR", {0,6}},  //

        { "river_corner_TR", {2,6}},  //
        { "river_corner_TL", {3,6}},  //

        { "river_vert", {2,5}},       //
        { "river_horiz", {3,5}},      //


        { "tree_base", {4,5}},        //
        { "tree_middle", {4,4}},      //
        { "tree_top", {4,3}},         //
        { "nothing", {0,7}}
    };
    map<string, string> aliasses = {

        { "A1", "convex_angle1" },
        { "A2", "convex_angle2" },

        { "S1", "convex_side1" },
        { "S2", "convex_side2" },

        { "A3", "convex_angle3" },
        { "A4", "convex_angle4" },


        { "F1", "forest_NW" },
        { "FN", "forest_N" },
        { "F2", "forest_NE" },

        { "FW", "forest_W" },
        { "FC", "forest_C" },
        { "FE", "forest_E" },

        { "F7", "forest_SW" },
        { "FS", "forest_S" },
        { "F4", "forest_SE" },

        { "FZ", "forest_S2" },


        { "T1", "tree_big_1" },
        { "T2", "tree_big_2" },
        { "T3", "tree_big_3" },
        { "T4", "tree_big_4" },


        { "d1", "stump1" },
        { "d2", "stump2" },
        { "FL", "flowers" },
        { "GS", "grass" },

        { "GD", "ground" },
        { "PL", "pool" },

        { "R2", "river_corner_BL" },
        { "R1", "river_corner_BR" },

        { "R3", "river_corner_TR" },
        { "R4", "river_corner_TL" },

        { "RH", "river_horiz" },
        { "RV", "river_vert" },


        { "tb", "tree_base" },
        { "tm", "tree_middle" },
        { "tt", "tree_top" },
        { "--", "nothing" },

    };
    vector<string> tile_strings = {
        "   GS GS                FW FC A2 -- ",
        "      GS GS       tt    F7 FS S2 -- ",
        "                  tb    tt    FW FC ",
        "   T1 T2    FL          tm    F7 FS ",
        "   T3 T4          GS    tb    F1 FN ",
        "                     F1 FN FN A4 -- ",
        "      R1 R2    F1 FN A4 -- -- -- -- ",
        "R1 RH R4 R3 R2 FW -- -- -- -- -- -- ",


    };
}


vector<Sprite> loadLevel(Texture& texture)
{
    vector<Sprite> sprite_map;
    Vector2f pos = { 0.f, 0.f };
    for (int i = 0; i < level::tile_strings.size(); i++)
    {
        std::string nommelacommetuveux = level::tile_strings[i];

        for (int b = 0; b < level::tile_strings[i].size(); b+=3)
        {
            vec2i var3 = level::tile_offsets["ground"];
            Sprite sprite;
            sprite.setTexture(texture);
            sprite.setTextureRect(IntRect(var3.x * 16, var3.y * 16, 16, 16));
            sprite.setScale(4, 4);
            sprite.setPosition(pos.x, pos.y);
            sprite_map.push_back(sprite);
            
            if (nommelacommetuveux[b] != ' ')
            {
                std::string var1 = level::tile_strings[i].substr(b, 2);
                if (level::aliasses.count(var1));
                {
                    std::string& var2 = level::aliasses[var1];
                    vec2i var3 = level::tile_offsets[var2];
                    Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setTextureRect(IntRect(var3.x * 16, var3.y * 16, 16, 16));
                    sprite.setPosition(pos.x, pos.y);
                    sprite.setScale(4, 4);
                    sprite_map.push_back(sprite);
                    pos.x += 64;
                }
            }
            else
            {
                pos.x += 64;
            }
        }
        pos.y += 64;
        pos.x = 0;
    }
    return sprite_map;
}

void treat_key_realese(Keyboard::Key key_code)
{
    switch (key_code)
    {

    case sf::Keyboard::S:
    case sf::Keyboard::Z:
        movement.y = 0;
        break;
    case sf::Keyboard::Q:
    case sf::Keyboard::D:
        movement.x = 0;
        break;

    default:
        break;
    }

}
void treat_key_press(Keyboard::Key key_code)
{
    switch (key_code)
    {

    case sf::Keyboard::S:
        movement.y = 0.1;
        break;
    case sf::Keyboard::Z:
        movement.y = -0.1;
        break;
    case sf::Keyboard::Q:
        movement.x = -0.1;
        break;
    case sf::Keyboard::D:
        movement.x = 0.1;
        break;

    default:
        break;
    }

}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 900), "Ca flingue");

    Texture texture;
    texture.loadFromFile("ghost.png");
    
    Sprite sprite;
    sprite.setTexture(texture);
   
    Texture texture_map;
    texture_map.loadFromFile("foresttiles2-t.png");
    vector<Sprite> sprite_map = loadLevel(texture_map);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                treat_key_press(event.key.code);
                break;
            case sf::Event::KeyReleased:
                treat_key_realese(event.key.code);
                break;

            default:
                break;
            }
        }

        sprite.move(movement);
        window.clear();
        for (int i = 0;i < sprite_map.size(); i++)
        {
            window.draw(sprite);
            window.draw(sprite_map[i]);
        }
        window.display();
    }

    return 0;
}