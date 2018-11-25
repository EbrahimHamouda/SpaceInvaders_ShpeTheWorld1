
#include "GameEngine.h"

extern Spirit_t Enemy_Ship[4];								// Enemy ship data	
extern Spirit_t Enemy_Ship_missles[8];				// Num of Enemy_Ship missles
extern Spirit_t SpaceShip_missles[8];					// Num of player ship missles
extern Spirit_t Player_Ship;									// Player ship data		
unsigned int en_x,k;

static void Creat_New_EnemyShip_missle(void)			// Generat random missles
{
	if(k==10)
	{
		Enemy_Ship_LaunchMissle(en_x);
		en_x++;
		k=0;
		if(en_x>=4)
		{
			en_x=0;
		}
	}
	k++;
}

static void Move_PlayerShip(float Adc_Value)
{
	if(Player_Ship.life>0)			// if  player ship still alive 
	{
		Player_Ship.x = (unsigned int)(Adc_Value * 19.69); // turn adc_value to position in the screen from 0:65  
		if(Player_Ship.x > 65)
		{
			Player_Ship.x=65;
		}
	}
}



void Game_Init(void)
{
	Buttons_init();											// buttons which used to fire	
	SysTick_Init();											// used to creat 30 hz peroidic interrupt to check inputs and draw  
	Init_Spirits();											// start a screen with Basic spirits
	ADC0_Init();												// used to record the position of player ship 
}

void Game_Controls(void)
{
	if(Button_read0())    						// check_Button 0
	{
		PlayerShipe_LaunchMissle();
	}
	
	if(Button_read1())								// check_Button 1
	{
		Player_Ship.life = 1;
	}
	
	Move_PlayerShip(ADC0_In()); 				// check ADC to the new poistion 
}

static void Missles_Rader()
{
	int i,j;
	for(i=0;i<8;i++)		
	{	
		for(j=0;j<4;j++) 																																											// check player_Misslles @ 4 enemyies																																											 
		{
			if(((SpaceShip_missles[i].y-LASERH-1)<= 10)&&(SpaceShip_missles[i].life==1))												
			{ 																																																	// check if missle reach Enemy_Ship height
				if((SpaceShip_missles[i].x >= Enemy_Ship[j].x)&&(SpaceShip_missles[i].x <= (Enemy_Ship[j].x+16)))	 
				{ 																																																// check if missle in rang Enemy_Ship width
					Enemy_Ship[j].life=0;																																						// Enemy_Ship get killed 
					SpaceShip_missles[i].life=0;																																		// missle destroyedd
					Creat_NewExploistion(Enemy_Ship[j].x,Enemy_Ship[j].y);																					// insert expolition
																																																					// insert Creat_NewExploistion sound
				}
			}
		}
		
		
		if((Enemy_Ship_missles[i].y > 39)&&(Enemy_Ship_missles[i].life>0))  	         												//Check Enemy missles @ Player ship 												
		{ 																																																		// check if missle @ Enemy_Ship height && it still alive
			if((Enemy_Ship_missles[i].x >=Player_Ship.x)&&(Enemy_Ship_missles[i].x <=Player_Ship.x+PLAYERW)&&(Player_Ship.life>0))
			{																																																		//check Enemy_missle @ range of player ship width && player ship still alive
				Enemy_Ship_missles[i].life=0; 																																		// missle destroyedd
				Player_Ship.life=0;																																								// player ship get killed 
				Creat_NewExploistion(Player_Ship.x,Player_Ship.y);																								// insert Expolition 
																																																					// insert Creat_NewExploistion sound
			}
		}
		
																																																					// check Enemy missles @ Bunker
		if((Enemy_Ship_missles[i].y > 34)&&(Enemy_Ship_missles[i].life>0))																		//check Missle @ hight of bunker && missle still alive	
		{																																															
			if((Enemy_Ship_missles[i].x >=33)&&(Enemy_Ship_missles[i].x <=33+BUNKERW))
			{																																																		//check Missle @ width of Bunker 
					Enemy_Ship_missles[i].life=0;																																		// missle destroyedd
			}
		}
		
		
	}	
}

void Game_Engine(void)
{
	Creat_New_EnemyShip_missle();
	Missles_Rader();
}

void Update_Screen(void)
{
	Draw();
}
