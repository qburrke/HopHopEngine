
#include "hop.hpp"
#include <iostream>


void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);
    game->monitor_key(KEY_SPACE);
    game->monitor_key(KEY_LEFT_SHIFT);


}

bool collision(hop::Image* hank, hop::Image* thing);
bool bunny_grounded(hop::Image *hank, hop::Image* terrain); 
bool collision(hop::Image* hank, hop::GameObject thing);

int main(){
    bool hank_right = true;
    hop::Game game("Bunny_Game");
    hop::Color pink={{1.0}, {0.4}, {0.7}};
    game.set_window_size(game.get_resolution_height(),game.get_resolution_height());
    game.run();
    hop::TextBox Title(100,700,2,hop::RED,"Welcome to Bunny Game!");
    // Custom colours
    hop::Color orange={{0.9}, {0.5}, {0.0}};
    hop::Color light_pink={{1}, {0.76}, {0.9}};
    hop::Color brown={{0.7}, {0.4}, {0.1}};
    
    // CARROT
    hop::Image carrot(850,960,100,60);
    carrot.create_triangle(70,60,0,0,90,20,orange);
    carrot.create_triangle(80,40,95,60,100,30,hop::GREEN);
    
    // stairs
    hop::Image stairs(0,0,1400,975);
    stairs.create_rectangle(0,0,200,750,brown); // hank spawn
    stairs.create_rectangle(200,650,200,100,brown);
    stairs.create_rectangle(400,650,200,150,brown);
    stairs.create_rectangle(600,750,170,50,brown);
    stairs.create_rectangle(200,0,1200,200,brown);
    stairs.create_rectangle(1000,0,200,800,brown);
    stairs.create_rectangle(770,375,150,200,brown);

    hop::Image hideout(770,200,300,175);
    hideout.create_rectangle(0,0,300,175,hop::WHITE);//bunny hideout

    // hank
    hop::Image hank(30,975,90,100);
    hank.create_rectangle(64,75,6,15,pink); //ear detail
    hank.create_rectangle(75,55,5,10,hop::BLACK); //bunny eye
    hank.create_rectangle(86,45,4,5,pink); //bunny nose
    hank.create_rectangle(50,35,40,40,hop::WHITE); //bunny head
    hank.create_rectangle(10,5,70,50,hop::WHITE); // bunny body
    hank.create_rectangle(60,75,10,25,hop::WHITE); //bunny ear
    hank.create_circle (0,15,10,hop::WHITE); //bunny tail
    hank.create_rectangle(20,0,10,10,hop::WHITE); //bunny back feet
    hank.create_rectangle(60,0,10,10,hop::WHITE); //bunny front feet
    
    hop::Sound boing = game.create_sound("boing.wav", false);

    monitor_keys(&game);
    int timer = 0;
    while(game.is_running()){
        game.update();
        timer++;

        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }

        if(game.key_pressed(KEY_SPACE)&&(bunny_grounded(&hank,&stairs))){
            
            if(hank_right){
                hank.move(200,100);   
            }
            else{
                hank.move(-200,100);
            }
            boing->play();
          }
        
        if(game.key_pressed(KEY_RIGHT)||game.key_held(KEY_RIGHT)){
            hank.move(10,0);
            if(!hank_right){
                hank.flip();
                hank_right = true;
            }
    }
        if(game.key_pressed(KEY_LEFT)||game.key_held(KEY_LEFT)){
            hank.move(-10,0);
            if(hank_right){
                hank.flip();
                hank_right = false;
            }
        }
        if(collision(&hank,&carrot)){
            carrot.move(50,0);
        }
        if(collision(&hank,&hideout)){
            hideout.move(1000,0);
        }
        if(!bunny_grounded(&hank,&stairs)){
            hank.move(0,-10);
        }
    }

    return 0;
}

bool collision(hop::Image* hank, hop::Image* thing){
    bool x_overlap = false;
    bool y_overlap = false;

    int o1_minx = hank->get_x();
    int o1_maxx = hank->get_x() + hank->get_width();
    int o1_miny = hank->get_y();
    int o1_maxy = hank->get_y() + hank->get_height(); 
    int o2_minx = thing->get_x();
    int o2_maxx = thing->get_x() + thing->get_width();
    int o2_miny = thing->get_y();
    int o2_maxy = thing->get_y() + thing->get_height(); 

    if((o1_minx<= o2_minx)&&(o1_maxx >= o2_minx)){
        x_overlap = true;
    }

    if((o2_minx<= o1_minx)&&(o2_maxx >= o1_minx)){
        x_overlap = true;
    }
    if((o1_miny<= o2_miny)&&(o1_maxy >= o2_miny)){
        y_overlap = true;
    }

    if((o2_miny<= o1_miny)&&(o2_maxy >= o1_miny)){
        y_overlap = true;
    }

    return x_overlap && y_overlap;

    return false;
}

bool bunny_grounded(hop::Image *hank, hop::Image* terrain){

    int bun_minx = hank->get_x();
    int bun_maxx = hank->get_x() + hank->get_width();

    for(auto obj: terrain->game_objects){
        bool x_overlap = false;
        int obj_minx = obj->x;
        int obj_maxx = obj->x + obj->width;
        int obj_top = obj->y+obj->height;
        if((bun_minx<= obj_minx)&&(bun_maxx >= obj_minx)){
            x_overlap = true;
        }
        if((obj_minx<= bun_minx)&&(obj_maxx >= bun_minx)){
            x_overlap = true;
        }

        if((x_overlap)&&(hank->get_y() > (obj_top-10))&&(hank->get_y()< (obj_top+10))){
            return true;
        }
    }
    return false;
}
