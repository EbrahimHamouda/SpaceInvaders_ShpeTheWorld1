#include "Spirits.h"

// worst case seniro of numbers of missles and Enemyies 
Spirit_t Enemy_Ship[4];
Spirit_t Enemy_Ship_missles[8];				// Num of Enemy_Ship missles i allow only 8 missles for Enemy_Ship ship 
Spirit_t SpaceShip_missles[8];		// Num of space ship missles i allow only 8 missles for player ship 
Spirit_t Player_Ship;
Spirit_t arr_Exploisitions[5];
static unsigned int
	SpaceShip_MisslesNum,											// num of missles alive
  Enemy_Ship_MisslesNum,
	Exploision_Num;
 int temp=0,flage=0;

void Init_Spirits(void)
{
	int i;  
	Nokia5110_Init();
	
  for(i=0;i<4;i++)																					// init Enimes_spirits
	{				
    Enemy_Ship[i].x = ENEMY_INIT_X*i;												// the top of the screen 
    Enemy_Ship[i].y = ENEMY_INIT_Y;																		
    Enemy_Ship[i].image = SmallEnemy_Ship30PointA; 					// it should be Chosen for Game Engine 
    Enemy_Ship[i].life = ALIVE;	
  }
	
	for(i=0;i<8;i++)																					// init Enmies missles
	{
		Enemy_Ship_missles[i].life=DEAD;												// init Enemy_missles being dead
	}
	
	for(i=0;i<5;i++)																					// init player_missles being dead
	{																													
		SpaceShip_missles[i].life=DEAD;													
	}

	
																														
	Player_Ship.x=PLAYER_INIT_X;															//Player ship init_x poisition
	Player_Ship.y=PLAYER_INIT_Y;															//Player ship init_y poisition
	Player_Ship.life=ALIVE;																		//Player ship life
	Player_Ship.image=PlayerShip0;														//Player ship image
	SpaceShip_MisslesNum = 0;																	//zero all missles
	Enemy_Ship_MisslesNum =0;																	//zero all missles
	Exploision_Num=0;																					//zero all exploision	
}

void Game_over(void)
{
	Nokia5110_Clear();
  Nokia5110_SetCursor(1, 1);
  Nokia5110_OutString("GAME OVER");
  Nokia5110_SetCursor(1, 2);
  Nokia5110_OutString("Nice try,");
  Nokia5110_SetCursor(1, 3);
  Nokia5110_OutString("Earthling!");
  Nokia5110_SetCursor(2, 4);
  Nokia5110_OutUDec(1234);
  Nokia5110_SetCursor(0, 0); // renders screen
}



static void Move_Enemy_Ship(unsigned int i)
{ 
	if(flage==0)
	{
		Enemy_Ship[i].x++;
		temp++;
	}
	else
	{
		Enemy_Ship[i].x--;
		temp--;
	}
	if(temp>=2)
	{
		flage=1;
	}
	if(temp<=-2)
	{
		flage=0;
	}
}

void Draw(void)
{ 
	int i;
	
  Nokia5110_ClearBuffer();																												// clear buffer
  Nokia5110_PrintBMP(33, 47 - PLAYERH, Bunker0, 0); 
	if(Player_Ship.life>0)																													// check if player ship still alive
	{
		Nokia5110_PrintBMP(Player_Ship.x, Player_Ship.y, Player_Ship.image, 0); // player ship middle bottom
	}

	
  for(i=0;i<4;i++)	// Ememys
	{																				
    if(Enemy_Ship[i].life > 0)  // check if they still alive
		{
      Nokia5110_PrintBMP(Enemy_Ship[i].x, Enemy_Ship[i].y, Enemy_Ship[i].image, 0);
			Move_Enemy_Ship(i);
    }
  }
	
	for(i=0;i<8;i++)		// Enemy_Ship_Misslles
	{
		if(Enemy_Ship_missles[i].y<40)															//check if reach board
		{
			if(Enemy_Ship_missles[i].life>0)													// check if still alive
			{
				Nokia5110_PrintBMP(Enemy_Ship_missles[i].x,Enemy_Ship_missles[i].y++,Enemy_Ship_missles[i].image,0); // Buffer the missle and increament y position after
			}
		}
		else
		{
			Enemy_Ship_missles[i].life=0;									// missle dead reach bottom screen
		}
	}
	for(i=0;i<8;i++)		// player_Misslles
	{
		if(SpaceShip_missles[i].y>LASERH)															//check if reach board
		{
			if(SpaceShip_missles[i].life>0)													// check if still alive
			{
				Nokia5110_PrintBMP(SpaceShip_missles[i].x,(SpaceShip_missles[i].y)--,SpaceShip_missles[i].image,0); // Buffer the missle and increament y position after
			}
		}
		else
		{
			SpaceShip_missles[i].life=0;									// missle dead reach bottom screen
		}
	}
	for(i=0;i<5;i++)		// Exploisions
	{
			if(arr_Exploisitions[i].life>0)													// check if still alive
			{
				arr_Exploisitions[i].life=0;
				Nokia5110_PrintBMP(arr_Exploisitions[i].x,(arr_Exploisitions[i].y),arr_Exploisitions[i].image,0); // Buffer the missle and increament y position after
			}
			
	}
 
	Nokia5110_DisplayBuffer();      // draw buffer
}

void Enemy_Ship_LaunchMissle(unsigned int num)
{
	if(Enemy_Ship[num].life>0)
	{		
		Enemy_Ship_missles[Enemy_Ship_MisslesNum].image=Missile0;
		Enemy_Ship_missles[Enemy_Ship_MisslesNum].life=1;
		Enemy_Ship_missles[Enemy_Ship_MisslesNum].x=(Enemy_Ship[num].x + 7);
		Enemy_Ship_missles[Enemy_Ship_MisslesNum].y=Enemy_Ship[num].y+MISSILEH;
		Enemy_Ship_MisslesNum++;
		if(Enemy_Ship_MisslesNum > 7)
		{
			Enemy_Ship_MisslesNum=0;
		}
	}
}

void PlayerShipe_LaunchMissle(void)
{
	/* check if
	*the player ship still alive
	*missle num in the buffer is dead to creat new one 
  *  
	*/
	if((Player_Ship.life>0)&&(SpaceShip_missles[SpaceShip_MisslesNum].life==0))	
	{	
			SpaceShip_missles[SpaceShip_MisslesNum].image=Laser0; 							//assign image,life,cordoniates
			SpaceShip_missles[SpaceShip_MisslesNum].life=1;
			SpaceShip_missles[SpaceShip_MisslesNum].x=(Player_Ship.x + 8);
			SpaceShip_missles[SpaceShip_MisslesNum].y=Player_Ship.y-PLAYERH;
			SpaceShip_MisslesNum++;																								//increament missle num to use new free place
			if(SpaceShip_MisslesNum > 7)
			{
				SpaceShip_MisslesNum=0;																							// to re-use the buffer of missles 
			}
	}
}
void Creat_NewExploistion(unsigned int x,unsigned int y)
{
	arr_Exploisitions[Exploision_Num].image=SmallExplosion0;
	arr_Exploisitions[Exploision_Num].x=x;
	arr_Exploisitions[Exploision_Num].y=y;
	arr_Exploisitions[Exploision_Num].life=1;
	Exploision_Num++;
	if(Exploision_Num>4)
	{
		Exploision_Num=0;
	}
}
