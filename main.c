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
#include "elements.c"
#include "elements.h"


void init();
void checkInput();
void updateSwitches();
void walkanim();
void lifeposition();
void assignsprite();
void assignpalette();
void assigntilespalette();
void isitloaded();
void elementsmenu();
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
UINT8 oldup[2];
UINT8 playerFlipped;
UINT8 lifebar_pos[2];
UINT8 movelistorderstart;
UINT8 movelistordercurrent;
UINT8 tiletoassign;
UINT8 movelistordernext;
UINT8 spritenb;
UINT8 spriteorder;
UINT8 paletteorder;
UINT8 magicka_player_loaded;
UINT8 elementsmenu_loaded;
UINT8 player_move_allowed;
UINT8 quitelementsmenu;
UINT8 recall_player_pos[2];
UINT8 elementsmenu_palette_loaded;
UINT8 magicka_player_palette_loaded;
UINT8 elements_tilesstart;
UINT8 magicka_player_tilesstart;
UINT8 interface_tilesstart;
UINT8 elementsmenu_tiles_assigned;
UINT8 magicka_player_tiles_assigned;
UINT8 magicka_player_tiles_loaded;
UINT8 elementsmenu_tiles_loaded;

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

UWORD elements_palette[] = {
	//scroll
	 elementsCGBPal0c0,elementsCGBPal0c1,elementsCGBPal0c2,elementsCGBPal0c3,
	 //water
	 elementsCGBPal1c0,elementsCGBPal1c1,elementsCGBPal1c2,elementsCGBPal1c3,
	 //life
	 elementsCGBPal2c0,elementsCGBPal2c1,elementsCGBPal2c2,elementsCGBPal2c3,
	 //ice
	 elementsCGBPal3c0,elementsCGBPal3c1,elementsCGBPal3c2,elementsCGBPal3c3,
	 //thunder
	 elementsCGBPal4c0,elementsCGBPal4c1,elementsCGBPal4c2,elementsCGBPal4c3,
	 //mana
	 elementsCGBPal5c0,elementsCGBPal5c1,elementsCGBPal5c2,elementsCGBPal5c3,
	 //earth
	 elementsCGBPal6c0,elementsCGBPal6c1,elementsCGBPal6c2,elementsCGBPal6c3,
	 //fire
	 elementsCGBPal7c0,elementsCGBPal7c1,elementsCGBPal7c2,elementsCGBPal7c3,
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

void isitloaded() {
	if (spritenb == 0) {
		magicka_player_loaded = 1;
	}
	else if (spritenb == 2) {
		elementsmenu_loaded = 1;
	}
}


void assigntilespalette() {
	if (spritenb == 0) {
		
		set_sprite_prop(0,0);
		set_sprite_prop(1,2);
		set_sprite_prop(2,1);
		set_sprite_prop(3,1);
		set_sprite_prop(4,0);
		set_sprite_prop(5,2);
		set_sprite_prop(6,1);
		set_sprite_prop(7,0);
		set_sprite_prop(8,0);
		set_sprite_prop(9,2);
		set_sprite_prop(10,1);
		set_sprite_prop(11,0);
		set_sprite_prop(12,0);
		set_sprite_prop(13,2);
		set_sprite_prop(14,1);
		set_sprite_prop(15,1);
		set_sprite_prop(16,0);
		set_sprite_prop(17,0);
		
	}
	else if (spritenb == 1) {
		set_sprite_prop(18,3);
		set_sprite_prop(19,3);
		set_sprite_prop(20,3);
		set_sprite_prop(21,3);
		set_sprite_prop(22,3);
		set_sprite_prop(23,3);
		set_sprite_prop(24,3);
		set_sprite_prop(25,3);
		set_sprite_prop(26,3);
		set_sprite_prop(27,3);
		set_sprite_prop(28,3);
		set_sprite_prop(29,3);
		set_sprite_prop(30,3);
	}
	else if (spritenb == 2) {
		
		set_sprite_prop(0,1);
		set_sprite_prop(1,1);
		set_sprite_prop(2,1);
		set_sprite_prop(3,1);
		set_sprite_prop(4,2);
		set_sprite_prop(5,2);
		set_sprite_prop(6,2);
		set_sprite_prop(7,2);
		set_sprite_prop(8,3);
		set_sprite_prop(9,3);
		set_sprite_prop(10,3);
		set_sprite_prop(11,3);
		set_sprite_prop(12,4);
		set_sprite_prop(13,4);
		set_sprite_prop(14,4);
		set_sprite_prop(15,4);
		set_sprite_prop(16,5);
		set_sprite_prop(17,5);
		set_sprite_prop(18,5);
		set_sprite_prop(19,5);
		set_sprite_prop(20,6);
		set_sprite_prop(21,6);
		set_sprite_prop(22,6);
		set_sprite_prop(23,6);
		set_sprite_prop(24,7);
		set_sprite_prop(25,7);
		set_sprite_prop(26,7);
		set_sprite_prop(27,7);
		set_sprite_prop(28,0);
		set_sprite_prop(29,0);
		set_sprite_prop(30,0);
		set_sprite_prop(31,0);
		
		}
		
}
		

void assignpalette() {
	if (spritenb == 0){
		paletteorder = 0;
	}
	else if (spritenb == 2){
		paletteorder = 0;
	}
	
	if (paletteorder+palettecount[spritenb] > 7) {
		paletteorder = 0;
	}
	
	
	set_sprite_palette(paletteorder,palettecount[spritenb],palettereference[spritenb]);
	
	paletteorder = paletteorder+palettecount[spritenb];	
}

void assignsprite() {
	if (spritenb==0 && magicka_player_tiles_loaded==0) {
		set_sprite_data(spriteorder, tilescount[spritenb], spritereference[spritenb]);
		spriteorder = spriteorder+tilescount[spritenb];
		magicka_player_tiles_loaded = 1;
		assigntiles(spritenb=0);
	}
	
	else if (spritenb==2 && elementsmenu_tiles_loaded==0){
		
		set_sprite_data(spriteorder, tilescount[spritenb], spritereference[spritenb]);
		spriteorder = spriteorder+tilescount[spritenb];
		elementsmenu_tiles_loaded=1;
		assigntiles(spritenb=2);
	}
	
	else if (spritenb != 2 && spritenb !=0){
		
		set_sprite_data(spriteorder, tilescount[spritenb], spritereference[spritenb]);
		spriteorder = spriteorder+tilescount[spritenb];
		assigntiles(spritenb=spritenb);
	}
}
	//tilesheet -> VRAM 
	//VRAM -> sprite list(OAM)
	
void assigntiles() {
	if(spritenb==0){
			movelistordercurrent=0;
			tiletoassign=0;
	}
	if (spritenb==2){
			movelistordercurrent=0;
			tiletoassign=18;
			movelistordernext = 18;
			
	}
	
	while (tiletoassign < (movelistordernext+tilescount[spritenb])) {

		set_sprite_tile(movelistordercurrent,tiletoassign);
		movelistordercurrent++;
		tiletoassign++;
	}
	movelistorderstart = movelistordercurrent-tilescount[spritenb];
	movelistordernext = movelistordercurrent;
	
	if (spritenb == 2) {
		elements_tilesstart = movelistorderstart;
		elementsmenu_tiles_assigned = 1;
		magicka_player_tiles_assigned = 0;
		
	}
	 if (spritenb == 0) {
		elementsmenu_tiles_assigned = 0;
		magicka_player_tiles_assigned = 1;
	}
		
	
	assignpalette();
	assigntilespalette();
	isitloaded();
	
}

void init() {
	movelistorderstart = 0;
	player_move_allowed = 1;
	spriteorder = 0;
	paletteorder = 0;
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
	player_tiles_right[0] = 1;
	player_tiles_right[1] = 3;
	player_tiles_left[0] = 0;
	player_tiles_left[1] = 2;
	
	set_bkg_palette(0,5,&testworld_palette[0]);
	set_bkg_data(0,28,testworldtiles);
	
	VBK_REG=1;
	set_bkg_tiles(0,0,32,32,testworldpalettemap);
	VBK_REG=0;
	set_bkg_tiles(0,0,32,32,testworldtilesmap);
	


	



	
	//NR52_REG = 0x8F;	// Turn on the sound
	//NR51_REG = 0x11;	// Enable the sound channels
	//NR50_REG = 0x77;	// Increase the volume to its max
	
	
	assignsprite(spritenb=0);
	// assignsprite(spritenb=1);
	// lifeposition();
}
void updateSwitches() {
		HIDE_WIN;
		SHOW_SPRITES;
		SHOW_BKG;
}

void elementsmenu() {
	
	quitelementsmenu = 0;
	
	recall_player_pos[0] = player_pos[0];
	recall_player_pos[1] = player_pos[1];
	move_sprite(player_tiles_left[0],200,200);
	move_sprite(player_tiles_left[1],200,200);
	move_sprite(player_tiles_right[0],200,200);
	move_sprite(player_tiles_right[1],200,200);
	
	
	if(elementsmenu_tiles_loaded == 0) {
		movelistordercurrent = 0;
		assignsprite(spritenb=2);
		elementsmenu_palette_loaded = 1;
		
	}
	
	else if (elementsmenu_tiles_assigned == 0) {
		
		// elements_tilesstart=0;
		movelistordercurrent = 0;
		movelistordernext=0;
		tiletoassign = 0;
		assigntiles(spritenb=2);
		// DISPLAY_OFF;
	}
	
	else if(elementsmenu_tiles_assigned ==1){
		move_sprite(1,30,30);
	}
	
	else if (elementsmenu_palette_loaded == 0) {
		
		assignpalette(spritenb=2);
		elementsmenu_palette_loaded = 1;
	}
	
	player_move_allowed = 0;
	set_bkg_palette(0,5,&testworld_palette_bw[0]);
	
	//UP
	move_sprite(0,80,18);
	move_sprite(1,88,18);
	move_sprite(2,80,26);
	move_sprite(3,88,26);
	//UPRIGHT
	move_sprite(4,133,38);
	move_sprite(5,141,38);
	move_sprite(6,133,46);
	move_sprite(7,141,46);
	//RIGHT
	move_sprite(8,150,80);
	move_sprite(9,158,80);
	move_sprite(10,150,88);
	move_sprite(11,158,88);
	//DOWNRIGHT
	move_sprite(12,133,122);
	move_sprite(13,141,122);
	move_sprite(14,133,130);
	move_sprite(15,141,130);
	
	//DOWN
	// move_sprite(elements_tilesstart+,80,142);
	// move_sprite(elements_tilesstart+,88,142);
	// move_sprite(elements_tilesstart+,80,150);
	// move_sprite(elements_tilesstart+,88,150);
	
	//DOWNLEFT
	move_sprite(16,27,122);
	move_sprite(17,35,122);
	move_sprite(18,27,130);
	move_sprite(19,35,130);
	//LEFT
	move_sprite(20,10,80);
	move_sprite(21,18,80);
	move_sprite(22,10,88);
	move_sprite(23,18,88);
	//UPLEFT
	move_sprite(24,30,38);
	move_sprite(25,38,38);
	move_sprite(26,30,46);
	move_sprite(27,38,46);
	
	//BOX
	move_sprite(28,40,75);
	move_sprite(29,40,83);
	move_sprite(30,40,88);
	
	
	
	
	while(quitelementsmenu == 0) {
	checkInput();
		if((joypad() & J_A)) {
			int u = movelistorderstart;
			int i=0;
			
			player_move_allowed = 1;
			set_bkg_palette(0,5,&testworld_palette[0]);
			spritenb=2;
			while (i<tilescount[spritenb]) {
				
				move_sprite(u,200,200);
				i++;
				u++;
				
			}
			quitelementsmenu = 1;
			
			paletteorder = 0;
			assigntiles(spritenb=0);
			assignpalette(spritenb=0);
			movelistordernext=0;
			elementsmenu_palette_loaded = 0;
			player_pos[0] = recall_player_pos[0];
			player_pos[1] = recall_player_pos[1];
		}
	}
}

void lifeposition() {
	if (playerWalking == 0) {
		if (playerFlipped == 0) {
		move_sprite(18,player_pos[0]-2,player_pos[1]+17);
		move_sprite(19,player_pos[0]+5,player_pos[1]+17);
		}
		if (playerFlipped == 1) {
		move_sprite(19,player_pos[0]-5,player_pos[1]+17);
		move_sprite(20,player_pos[0]+2,player_pos[1]+17);
		}
	}
	if (playerWalking == 1) {
		if (playerFlipped == 0) {
		move_sprite(19,player_pos[0]-4,player_pos[1]+17);
		move_sprite(20,player_pos[0]+3,player_pos[1]+17);
		}
		if (playerFlipped == 1) {
		move_sprite(19,player_pos[0]-3,player_pos[1]+17);
		move_sprite(20,player_pos[0]+4,player_pos[1]+17);
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

    if ((joypad() & J_B) && (player_move_allowed == 1)) {
		elementsmenu();
	}	
	
	
	
	
	if((joypad() & J_A) ) {
	
    }
	
	if ((magicka_player_loaded == 1) && (player_move_allowed == 1)) {
		
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

	
	
	
}
