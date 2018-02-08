#include <gb/gb.h>
#include <gb/cgb.h>
#include "alphabet_lined.c"
#include "blankscreen.c"
#include "sprites.c"
#include "magicka_player.c"
#include "magicka_player.h"
#include "interface_tiles.c"
#include "interface_tiles.h"
#include "testworldtiles.c"
#include "testworldtiles.h"
#include "testworldtiles_bw.c"
#include "testworldtiles_bw.h"
#include "testworldtilesmap.c"
// #include "testworldtilesmap_bw.c"
#include "testworldpalettemap.c"
#include "testworldpalettemap_bw.c"
#include "spritelist.c"


void init();
void checkInput();
void updateSwitches();
void walkanim();
void lifeposition();
void assigntiles();

UINT8 player_pos[2];
UINT8 player_tiles_left[2];
UINT8 player_tiles_right[2];
UINT8 playerWalking;
UINT8 playerWalkingTimer;
UINT8 playerWalkingState;
UINT8 spr;
UINT8 oldleft[2];
UINT8 oldright[2];
UINT8 playerFlipped;
UINT8 lifebar_pos[2];
UINT8 tiletoassign;
UINT8 placetoassign;



UWORD testworld_palette_bw[] = {
	//p0
	testworldtiles_bwCGBPal0c0,
	testworldtiles_bwCGBPal0c1,
	testworldtiles_bwCGBPal0c2,
	testworldtiles_bwCGBPal0c3,
	//p1
	testworldtiles_bwCGBPal1c0,
	testworldtiles_bwCGBPal1c1,
	testworldtiles_bwCGBPal1c2,
	testworldtiles_bwCGBPal1c3,
	//p2
	testworldtiles_bwCGBPal2c0,
	testworldtiles_bwCGBPal2c1,
	testworldtiles_bwCGBPal2c2,
	testworldtiles_bwCGBPal2c3,
	//p3
	testworldtiles_bwCGBPal3c0,
	testworldtiles_bwCGBPal3c1,
	testworldtiles_bwCGBPal3c2,
	testworldtiles_bwCGBPal3c3,
	//p4
	testworldtiles_bwCGBPal4c0,
	testworldtiles_bwCGBPal4c1,
	testworldtiles_bwCGBPal4c2,
	testworldtiles_bwCGBPal4c3
};
	
UWORD testworld_palette[] = {
	//p0
	testworldtilesCGBPal0c0,testworldtilesCGBPal0c1,testworldtilesCGBPal0c2,testworldtilesCGBPal0c3,
	//p1
	testworldtilesCGBPal1c0,testworldtilesCGBPal1c1,testworldtilesCGBPal1c2,testworldtilesCGBPal1c3,
	//p2
	testworldtilesCGBPal2c0,testworldtilesCGBPal2c1,testworldtilesCGBPal2c2,testworldtilesCGBPal2c3,
	//p3
	testworldtilesCGBPal3c0,testworldtilesCGBPal3c1,testworldtilesCGBPal3c2,testworldtilesCGBPal3c3,
	//p4
	testworldtilesCGBPal4c0,testworldtilesCGBPal4c1,testworldtilesCGBPal4c2,testworldtilesCGBPal4c3,
};

UWORD interface_palette[] = {
	//life bar
	interface_tilesCGBPal0c0, interface_tilesCGBPal0c1,interface_tilesCGBPal0c2,interface_tilesCGBPal0c3
};

UWORD magicka_player_palette[] = {
	//tete (alpha, gold, rouge, noir)
	magicka_playerCGBPal0c0, magicka_playerCGBPal0c1, magicka_playerCGBPal0c2,magicka_playerCGBPal0c3,
	//tronc (alpha, gold, rouge, brun)
	magicka_playerCGBPal1c0,magicka_playerCGBPal1c1,magicka_playerCGBPal1c2,magicka_playerCGBPal1c3,
	//baton (alpha, gold, rouge, bleu clair)
	magicka_playerCGBPal2c0,magicka_playerCGBPal1c1,magicka_playerCGBPal1c2,magicka_playerCGBPal2c3,
	
};



void main() {

	init();
	
	while(1) {
		
		updateSwitches();
		checkInput();
		walkanim();
		// lifeposition();

		wait_vbl_done();
		
		// Game code here
	}
	
}



void assigntiles() {
	for (tiletoassign = 0; placetoassign < tilesnb[0]; placetoassign ++) {
		
		set_sprite_tile(placetoassign,tiletoassign,spritetoassign[0]);
		
		tiletoassign++;
	}
}

void init() {
	placetoassign = 0;
	// tiletoassign = 0;
	player_pos[0] = 30;
	player_pos[1] = 50;
	lifebar_pos[0] = 20;
	lifebar_pos[1] = 20;
	playerWalking = 0;
	playerWalkingTimer = 0;
	playerWalkingState = 0;
	
	spr = 0;
	oldleft[0] = 0;
	oldright[0] = 1;
	oldleft[1] = 2;
	oldright[1] = 3;
	playerFlipped = 0;
	DISPLAY_ON;		// Turn on the display
	
	SPRITES_8x8;
	
	
	set_bkg_palette(0,5,&testworld_palette[0]);
	set_bkg_data(0,28,testworldtiles);
	
	VBK_REG=1;
	set_bkg_tiles(0,0,32,32,testworldpalettemap);
	VBK_REG=0;
	set_bkg_tiles(0,0,32,32,testworldtilesmap);
	// VBK_REG=0;
	
	set_sprite_palette(0,3, &magicka_player_palette[0]); //n° palette to stock on, nb of palettes to load
	set_sprite_data(0,18,magicka_player);
	
	
	
	// set_sprite_palette(3,1,&interface_palette[0]);
	// set_sprite_data(12,14,interface_tiles);
	
	player_tiles_right[0] = 1;
	player_tiles_right[1] = 3;
	player_tiles_left[0] = 0;
	player_tiles_left[1] = 2;

	
	// spritetoassign = magicka_player;
	
	
	// set_sprite_tile(0,0,magicka_player);  //assign a loaded tile to a sprite move(list) slot
	// set_sprite_tile(1,1,magicka_player);
	// set_sprite_tile(2,2,magicka_player);
	// set_sprite_tile(3,3,magicka_player);
	// set_sprite_tile(4,4,magicka_player);
	// set_sprite_tile(5,5,magicka_player);
	// set_sprite_tile(6,6,magicka_player);
	// set_sprite_tile(7,7,magicka_player);
	// set_sprite_tile(8,8,magicka_player);
	// set_sprite_tile(9,9,magicka_player);
	// set_sprite_tile(10,10,magicka_player);
	// set_sprite_tile(11,11,magicka_player);
	

	
	// set_sprite_tile(12,12,interface_tiles);
	// set_sprite_tile(13,13,interface_tiles);
	// set_sprite_tile(14,14,interface_tiles);
	// set_sprite_tile(15,15,interface_tiles);
	// set_sprite_tile(16,16,interface_tiles);
	// set_sprite_tile(17,17,interface_tiles);
	// set_sprite_tile(18,18,interface_tiles);
	// set_sprite_tile(19,19,interface_tiles);
	// set_sprite_tile(20,20,interface_tiles);
	// set_sprite_tile(21,21,interface_tiles);
	// set_sprite_tile(22,22,interface_tiles);
	// set_sprite_tile(23,23,interface_tiles);
	// set_sprite_tile(24,24,interface_tiles);
	
	


	set_sprite_prop(0,0);
	set_sprite_prop(1,2);
	set_sprite_prop(2,1);
	set_sprite_prop(3,1);
	set_sprite_prop(5,2);
	set_sprite_prop(6,1);
	set_sprite_prop(9,2);
	set_sprite_prop(10,1);
	set_sprite_prop(11,0);
	set_sprite_prop(12,3);
	set_sprite_prop(13,3);
	
	// set_bkg_palette(0,1,&testworld_palette[0]);
	// set_bkg_palette(1,1,&testworld_palette[1]);
	// set_bkg_palette(2,1,&testworld_palette[2]);
	// set_bkg_palette(3,1,&testworld_palette[3]);
	// set_bkg_palette(4,1,&testworld_palette[4]);
	
	
	//NR52_REG = 0x8F;	// Turn on the sound
	//NR51_REG = 0x11;	// Enable the sound channels
	//NR50_REG = 0x77;	// Increase the volume to its max
	
	// move_sprite(12,player_pos[0],player_pos[1]+16);
	// move_sprite(13,player_pos[0]+8,player_pos[1]+16);
	assigntiles();
}
void updateSwitches() {
		HIDE_WIN;
		SHOW_SPRITES;
		SHOW_BKG;
}


void lifeposition() {
	if (playerWalking == 0) {
		if (playerFlipped == 0) {
		move_sprite(12,player_pos[0]-2,player_pos[1]+17);
		move_sprite(13,player_pos[0]+5,player_pos[1]+17);
		}
		if (playerFlipped == 1) {
		move_sprite(12,player_pos[0]-5,player_pos[1]+17);
		move_sprite(13,player_pos[0]+2,player_pos[1]+17);
		}
	}
	if (playerWalking == 1) {
		if (playerFlipped == 0) {
		move_sprite(12,player_pos[0]-4,player_pos[1]+17);
		move_sprite(13,player_pos[0]+3,player_pos[1]+17);
		}
		if (playerFlipped == 1) {
		move_sprite(12,player_pos[0]-3,player_pos[1]+17);
		move_sprite(13,player_pos[0]+4,player_pos[1]+17);
		}
	}
}
	
void walkanim() {
	
	if (playerWalking == 1) {
		playerWalkingTimer = playerWalkingTimer+1;
		
		if (playerWalkingState == 0) {
		player_tiles_right[0] = 5;
		player_tiles_right[1] = 7;
		player_tiles_left[0] = 4;
		player_tiles_left[1] = 6;
		}
		
		if (playerWalkingState == 1) {
		player_tiles_right[0] = 9;
		player_tiles_right[1] = 11;
		player_tiles_left[0] = 8;
		player_tiles_left[1] = 10;
		}
		
		if ((playerWalkingTimer == 10) && (playerWalkingState == 0)) {
			playerWalkingTimer = 0;
			playerWalkingState = 1;
			
		}
		
		if ((playerWalkingTimer == 10) && (playerWalkingState == 1)) {
			playerWalkingTimer = 0;
			playerWalkingState = 0;
			
		}
		
		
	}
	if (playerWalking == 0) {
		player_tiles_right[0] = 1;
		player_tiles_right[1] = 3;
		player_tiles_left[0] = 0;
		player_tiles_left[1] = 2;
		playerWalkingState = 0;
		
	}
}
	
void checkInput() {

    if (joypad() & J_B) {
		set_bkg_palette(0,5,&testworld_palette_bw[0]);
		// set_bkg_tiles(0,0,20,18,blankScreen);
	}	// The B button was pressed!
	if(joypad() & J_A) {
		set_bkg_palette(0,5,&testworld_palette[0]);
		// set_bkg_tiles(6,7,7,2,helloworld);
		// The A button was pressed!
		
		
    }
	
	// UP
	if (joypad() & J_UP) {
		
		
		if (player_pos[1] == 30) {
			scroll_bkg(0,-1);
		}
		
		if (player_pos[1] != 30) {
			player_pos[1]--;
		}

		
		move_sprite(oldleft[0],200,200);
		move_sprite(oldleft[1],200,200);
		move_sprite(oldright[0],200,200);
		move_sprite(oldright[1],200,200);
		
		if (playerFlipped == 0) {
			move_sprite(player_tiles_right[0], player_pos[0]+8, player_pos[1]);
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			move_sprite(player_tiles_right[1],player_pos[0]+8,player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) & ~S_FLIPX);
		}
		if (playerFlipped == 1) {
			move_sprite(player_tiles_right[0], player_pos[0]-8, player_pos[1]);
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			move_sprite(player_tiles_right[1], player_pos[0]-8, player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) | S_FLIPX);
		}
		
		
		
		oldleft[0] = player_tiles_left[0];
		oldleft[1] = player_tiles_left[1];
		oldright[0] = player_tiles_right[0];
		oldright[1] = player_tiles_right[1];
		
		playerWalking = 1;
	}

	// DOWN
	if (joypad() & J_DOWN) {
		
		if (player_pos[1] != 134) {
			player_pos[1]++;
		}
		if (player_pos[1] == 134) {
			scroll_bkg(0,1);
		}
		
		move_sprite(oldleft[0],200,200);
		move_sprite(oldleft[1],200,200);
		move_sprite(oldright[0],200,200);
		move_sprite(oldright[1],200,200);
		
		if (playerFlipped == 0) {
			move_sprite(player_tiles_right[0], player_pos[0]+8, player_pos[1]);
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			move_sprite(player_tiles_right[1],player_pos[0]+8,player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) & ~S_FLIPX);
		}
		if (playerFlipped == 1) {
			move_sprite(player_tiles_right[0], player_pos[0]-8, player_pos[1]);
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			move_sprite(player_tiles_right[1], player_pos[0]-8, player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) | S_FLIPX);
		}
		
		
		
		oldleft[0] = player_tiles_left[0];
		oldleft[1] = player_tiles_left[1];
		oldright[0] = player_tiles_right[0];
		oldright[1] = player_tiles_right[1];
		
		
		playerWalking = 1;
		
	}

	// LEFT
	if (joypad() & J_LEFT)  {
		
		if (player_pos[0] != 70) {
			player_pos[0]--;
		}
		if (player_pos[0] == 70) {
			scroll_bkg(-1,0);
		}
		
		

		move_sprite(oldleft[0],200,200);
		move_sprite(oldleft[1],200,200);
		move_sprite(oldright[0],200,200);
		move_sprite(oldright[1],200,200);
		
		set_sprite_prop(player_tiles_right[0],get_sprite_prop(player_tiles_right[0])  | S_FLIPX);
		set_sprite_prop(player_tiles_right[1],get_sprite_prop(player_tiles_right[1])  | S_FLIPX);
		set_sprite_prop(player_tiles_left[0],get_sprite_prop(player_tiles_left[0])  | S_FLIPX);
		set_sprite_prop(player_tiles_left[1],get_sprite_prop(player_tiles_left[1]) | S_FLIPX);
		
		if (!((joypad() & J_RIGHT))) {
			playerFlipped = 1;
		}
		
		move_sprite(player_tiles_right[0], player_pos[0]-8, player_pos[1]);
		move_sprite(player_tiles_right[1], player_pos[0]-8, player_pos[1]+8);
		move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
		move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
		
		oldleft[0] = player_tiles_left[0];
		oldleft[1] = player_tiles_left[1];
		oldright[0] = player_tiles_right[0];
		oldright[1] = player_tiles_right[1];
		
		playerWalking = 1;		
		

	}	
	
	// RIGHT
	if ((joypad() & J_RIGHT) && !(joypad() & J_LEFT)) {
		
		
		
	
		if (player_pos[0] != 90) {
			player_pos[0]++;
		}
		if (player_pos[0] == 90) {
			scroll_bkg(1,0);
		}
		
			move_sprite(oldleft[0],200,200);
			move_sprite(oldleft[1],200,200);
			move_sprite(oldright[0],200,200);
			move_sprite(oldright[1],200,200);
			
			set_sprite_prop(player_tiles_left[0],get_sprite_prop(player_tiles_left[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[0],get_sprite_prop(player_tiles_right[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_left[1],get_sprite_prop(player_tiles_left[1]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[1],get_sprite_prop(player_tiles_right[1]) & ~S_FLIPX);
			
			if (!(joypad() & J_LEFT)) {
				playerFlipped = 0;
			}
			
			move_sprite(player_tiles_right[0], player_pos[0]+8, player_pos[1]);
			
			move_sprite(player_tiles_right[1],player_pos[0]+8,player_pos[1]+8);
			
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
				
			
			
			oldleft[0] = player_tiles_left[0];
			oldleft[1] = player_tiles_left[1];
			
			oldright[0] = player_tiles_right[0];
			oldright[1] = player_tiles_right[1];

			playerWalking = 1;
		
		
	}
	
	//NOT MOVING
	if (!(joypad() & J_RIGHT) &&  !(joypad() & J_LEFT) && !(joypad() & J_UP) && !(joypad() & J_DOWN)) {
		
		
		
		move_sprite(oldleft[0],200,200);
		move_sprite(oldleft[1],200,200);
		move_sprite(oldright[0],200,200);
		move_sprite(oldright[1],200,200);
		
		if (playerFlipped == 0) {
			move_sprite(player_tiles_right[0], player_pos[0]+8, player_pos[1]);
			
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			
			move_sprite(player_tiles_right[1],player_pos[0]+8,player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) & ~S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) & ~S_FLIPX);
		}
		
		if (playerFlipped == 1) {
			move_sprite(player_tiles_right[0], player_pos[0]-8, player_pos[1]);
			move_sprite(player_tiles_left[0],player_pos[0],player_pos[1]);
			move_sprite(player_tiles_left[1],player_pos[0],player_pos[1]+8);
			move_sprite(player_tiles_right[1], player_pos[0]-8, player_pos[1]+8);
			
			set_sprite_prop(player_tiles_left[0], get_sprite_prop(player_tiles_left[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_left[1], get_sprite_prop(player_tiles_left[1]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[0], get_sprite_prop(player_tiles_right[0]) | S_FLIPX);
			set_sprite_prop(player_tiles_right[1], get_sprite_prop(player_tiles_right[1]) | S_FLIPX);
		}
		
		oldleft[0] = player_tiles_left[0];
		oldleft[1] = player_tiles_left[1];
		
		oldright[0] = player_tiles_right[0];
		oldright[1] = player_tiles_right[1];
		playerWalking = 0;
	}
	
	
	
	
	
}
