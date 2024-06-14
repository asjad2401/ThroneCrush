// buttons.c
//this file contains definitions of all button related functions
#include "raylib.h"
#include "declarations.h"
#include "buttons.h"


/*this function is used for creating buttons
  it takes as arguments various values for posions and dimensions related to butons
  it creates a temporary button "createdbutton" and uses the passed arguments to assign
  values to all parameters of the button (which is a struct)
  eventually the function returns the "created button" as a Button which can be stored in a
  new variable upon call
*/

Button createButton(int posx,int posy,float buttonWidth,float buttonHeight){
    Button createdbutton = {
        posY : posy,
        posX : posx,
        ButtonWidth : buttonWidth,
        ButtonHeight : buttonHeight,
        textXpos : (posx/2 + buttonWidth)+30,
        textYpos : (posy/2 +buttonHeight)+60

    };
    return createdbutton;

}