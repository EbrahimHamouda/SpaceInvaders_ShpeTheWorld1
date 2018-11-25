
#include "Spirits.h"
#include "ADC.h"
#include "Buttons.h"
#include "systick.h"




void Game_Init(void);
void Game_Controls(void);


/* Game_Engine 
 *creat Enemy_Ship missles in random 
 *check Enemy_Ship missles hit player
 *check player missles hit Enemy_Ship
 *creat explotion  
*/

void Game_Engine(void);
void Update_Screen(void);
