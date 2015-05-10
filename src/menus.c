#include <pebble.h>
#include "menus.h"

void update_menu(GameData* gamedata){
  update_menu_layer(menudata);
  draw_menu_layer(menudata);
}

void update_menu_layer(MenuData* menudata){
  int buttonpress = check_current_button(gamedata);
  updatemenuselection(gamedata, 0, MENUITEMSCNT);
    
    //if the island does not like the player, do not allow trade to happen.
    
    if(manageislandallegiance(gamedata, gamedata->playerisland, 0) > -10){
      //IF SELECT IS HIT AND MENULAYER IS 0 go into the second menu layer
      //the second menu layer checks which layer this menu is currently on.  Menu 0 and 1 are tied
      //together
      if(gamedata->currentmenu[0] >=0 && gamedata->currentmenu[0] <= 3 && gamedata->menulayer == 0
         && gamedata->uphit == 1 && gamedata->downhit == 1 && gamedata->buttonrelease == 1){
        gamedata->menulayer = 1;
        gamedata->buttonrelease = 0;
       }
    }
    if(gamedata->currentmenu[0] == 4 && buttonpress == 3 && gamedata->buttonrelease == 1){
      gamedata->menulayer = 2;
      gamedata->buttonrelease = 0;
    }
    
    //if exit is highlighted leave
    if(gamedata->currentmenu[0] == 5 && buttonpress == 3){
      exitisland(gamedata);
      gamedata->playersailsdeployed = 0;
      gamedata->currentmenu[0] = 0;
      gamedata->gamemode = 'p';
      gamedata->buttonrelease = 0;
    }
}

void updatemenuselection(GameData* gamedata, int menulayer, int layeritemscount){
  if(gamedata->downhit == 1 && gamedata->uphit == 0 && gamedata->buttonrelease == 1){
      gamedata->currentmenu[menulayer] = ((gamedata->currentmenu[menulayer] + 1) % layeritemscount);
      gamedata->buttonrelease = 0;
  }
  //UP PRESSED
  if(gamedata->uphit == 1 && gamedata->downhit == 0 && gamedata->buttonrelease == 1){
    gamedata->currentmenu[menulayer] = ((gamedata->currentmenu[menulayer] - 1) % layeritemscount);
    gamedata->buttonrelease = 0;
    if(gamedata->currentmenu[menulayer] < 0)
      gamedata->currentmenu[menulayer] = layeritemscount - 1;
  }
}


void draw_menu_layer(MenuData* menudata){
  //always draw the base menu
  if(gamedata.menulayer == 0 || gamedata.menulayer == 1 || gamedata.menulayer == 2)
    draw_menu_layer(this_layer, ctx, 0, 0, 15); //the base menu layer
  if(gamedata.menulayer == 1)//buysellmenu
    draw_menu_layer(this_layer, ctx, 1, 57, 15);
  if(gamedata.menulayer == 2) // the islands upgrade menu
    draw_menu_layer(this_layer, ctx, 2, 57, 15);
  if(gamedata.menulayer == 3) //the ship pillage menu
    draw_menu_layer(this_layer, ctx, 3, 0, 15);
  if(gamedata.menulayer == 4)//the notifications menu
    draw_menu_layer(this_layer, ctx, 4, 0, 0);
  if(gamedata.menulayer == 5) //the player start menu
    draw_menu_layer(this_layer, ctx, 5, 0, 15);
  if(gamedata.menulayer == 6 || gamedata.menulayer == 7 || gamedata.menulayer == 14)
    draw_menu_layer(this_layer, ctx, 6, 0, 15);
  if(gamedata.menulayer == 7 || gamedata.menulayer == 8)
    draw_menu_layer(this_layer, ctx, 7, 0, 15);
  if(gamedata.menulayer == 8)
    draw_menu_layer(this_layer, ctx, 8, 57, 15);
  if(gamedata.menulayer == 9)
    draw_menu_layer(this_layer, ctx, 9, 0, 15);
  if(gamedata.menulayer == 10)
    draw_menu_layer(this_layer, ctx, 10, 0, 15);
  if(gamedata.menulayer == 11)
    draw_menu_layer(this_layer, ctx, 11, 57, 15);
  if(gamedata.menulayer == 12)
    draw_menu_layer(this_layer, ctx, 12, 57, 15);
  if(gamedata.menulayer == 13)
    draw_menu_layer(this_layer, ctx, 13, 57, 15);
  if(gamedata.menulayer == 14)
    draw_menu_layer(this_layer, ctx, 14, 57, 15);
}


void draw_menu_layer(Layer *this_layer, GContext *ctx, int menulayernumber, int x, int y){
  
  graphics_context_set_text_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  
  //any layer: draw the background box, then draw the highlighting box, then draw the text
  //base menu layer
  if(menulayernumber == 0){
    char totalmenu[65];
    //create the char array for the menu    
    snprintf(totalmenu, sizeof(totalmenu), "Island %i\n Metal:%d\n Wood:%d\n Stone:%d\n Food:%d\n Island:\n -Exit-", gamedata.playerisland + 1,
           gamedata.islandscargo[gamedata.playerisland][0],
           gamedata.islandscargo[gamedata.playerisland][1],
           gamedata.islandscargo[gamedata.playerisland][2],
           gamedata.islandscargo[gamedata.playerisland][3]);
    drawmenuandbox(this_layer, ctx, 0, 0, MENUITEMSCNT, x, y, 57, 1, totalmenu);
    //draw two white bars to display which resource is being bought or sold
    int producerectpos, consumerectpos;
    //find where the island produce is on the menu
    producerectpos = 19 + ((gamedata.islandstypes[gamedata.playerisland] + 1) * 15) - (gamedata.islandstypes[gamedata.playerisland] + 1);
    //find where island consumption is on the menu
    if(gamedata.islandstypes[gamedata.playerisland] == 0){
      consumerectpos = 19 + (3 * 15) - 3; //2 + 2 + 15 + (2 * 15) - 2;
    }
    if(gamedata.islandstypes[gamedata.playerisland] == 1){
      consumerectpos = 19 + (4 * 15) - 4; //2 + 2 + 15 + (3 * 15) - 3;
    }
    if(gamedata.islandstypes[gamedata.playerisland] == 2){
      consumerectpos = 19 + (2 * 15) - 2; //2 + 2 + 15 + (1 * 15) - 1;
    }
    if(gamedata.islandstypes[gamedata.playerisland] == 3){
      consumerectpos = 19 + (1 * 15) - 1; //2 + 2 + 15 + (0 * 15) - 0;
    }
    //draw the icons for the two
    graphics_context_set_fill_color(ctx, GColorWhite);
    GRect producerect = GRect(53, producerectpos, 2, 11);
    GRect consumerect = GRect(54, consumerectpos, 1, 11);
    graphics_fill_rect(ctx, producerect, 0, GCornerNone);
    graphics_fill_rect(ctx, consumerect, 0, GCornerNone);
    graphics_context_set_fill_color(ctx, GColorBlack);
  }
  //menu layer for buying and selling resources
  if(menulayernumber == 1){
    //needs to be made better later, shouldn't calculate for all at once, should do one at a time
    //this change will increase performance
    ResourceValues buysellvals = getmoneyvalue(&gamedata, gamedata.playerisland);
    int resourcevalue = 0;
    if(gamedata.currentmenu[0] == 0)
      resourcevalue = buysellvals.metalvalue;
    if(gamedata.currentmenu[0] == 1)
      resourcevalue = buysellvals.woodvalue;
    if(gamedata.currentmenu[0] == 2)
      resourcevalue = buysellvals.stonevalue;
    if(gamedata.currentmenu[0] == 3)
      resourcevalue = buysellvals.foodvalue;
    gamedata.currentcosts = resourcevalue;
    //end area that needs changing 
    char menu2text[27];
    snprintf(menu2text, sizeof(menu2text), " -Back-\n Buy:%i\n Sell:", resourcevalue);
    drawmenuandbox(this_layer, ctx, 0, 1, MENU2ITEMSCNT, x, y, 54, 0, menu2text);
  }
  //menu layer for upgrade purchases
  if(menulayernumber == 2){
    graphics_fill_rect(ctx, GRect(x,y,80,15 + 4 + y+(MENU3ITEMSCNT - 1)*15 - MENU3ITEMSCNT), 0, GCornerNone);
    graphics_draw_rect(ctx, GRect(x, 2 + y+(gamedata.currentmenu[2]+1)*15 - gamedata.currentmenu[2], 80, 15));
    GRect layer3text = GRect(x,y,80, 80);
    //get needed data
    //find current upgrade level, and change the price for that upgrade by a function on the constant
    //BASE_VALUE_UPGRADENAME
    int cargoprice = 1;
    int speedprice = 1;
    
    char secondmenulayer[67];
    int upgradeprices[3];
    for(int i = 0; i < 2; i++)
      upgradeprices[i] = check_player_upgrade_price(&gamedata, i);
    cargoprice = upgradeprices[0];
    speedprice = upgradeprices[1];
    snprintf(secondmenulayer, sizeof(secondmenulayer), "Faction:%i\n BuySu:%i\n UpCrgo:%i\n UpSpd: %i\n DnSpd: %i -Back-", manageislandallegiance(&gamedata, gamedata.playerisland, 0), BASE_PRICE_SUPPLIES, cargoprice, speedprice, speedprice);
    graphics_draw_text(ctx, secondmenulayer, fonts_get_system_font(FONT_KEY_FONT_FALLBACK), layer3text, GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  }
  //menu layer for ship interactions
  if(menulayernumber == 3){
    char thirdmenulayer[25];
    char shipcontents[10] = "none";
    //check what the ship has in it's cargo hold
    if(gamedata.shipstype[gamedata.playership] == 0)
      snprintf(shipcontents, sizeof(shipcontents), "Metal");
    if(gamedata.shipstype[gamedata.playership] == 1)
      snprintf(shipcontents, sizeof(shipcontents), "Wood");
    if(gamedata.shipstype[gamedata.playership] == 2)
      snprintf(shipcontents, sizeof(shipcontents), "Stone");
    if(gamedata.shipstype[gamedata.playership] == 3)
      snprintf(shipcontents, sizeof(shipcontents), "Food");
    if(gamedata.shipscargo[gamedata.playership] == 0)
      snprintf(shipcontents, sizeof(shipcontents), "None");
    snprintf(thirdmenulayer, sizeof(thirdmenulayer), " %s\n -Back-:\n Pillage", shipcontents);
    drawmenuandbox(this_layer, ctx, 0, 3, MENU4ITEMSCNT, x, y, 50, 1, thirdmenulayer);
  }
  //menu layer for notification pop ups
  if(menulayernumber == 4){
    GRect layer5area = GRect(8, 10, 128, 134);
    graphics_fill_rect(ctx, layer5area, 0, GCornerNone);
    GRect layer5text = GRect(8, 10, 128, 180);
    graphics_draw_text(ctx, gamedata.notificationtext, fonts_get_system_font(FONT_KEY_FONT_FALLBACK), layer5text, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  }
  if(menulayernumber == 5){ //player "start menu"
    drawmenuandbox(this_layer, ctx, 0, 5, MENU6ITEMSCNT, x, y, 54, 0, " Map:\n Event:\n Tutorial\n Build\n -Back-");
  }
  if(menulayernumber == 6){
    char menu7text[50];
    snprintf(menu7text, sizeof(menu7text), " $: %i\n Resource:\n Ships:\n Money:\n -Back-", gamedata.storagewallet);
    drawmenuandbox(this_layer, ctx, 0, 6, MENU7ITEMSCNT, x, y, 54, 1, menu7text);
  }
  if(menulayernumber == 7){
    char menu7text[100];
    snprintf(menu7text, sizeof(menu7text), " Metal: %i\n Wood: %i\n Stone%i\n Food %i\n -Back-", gamedata.islandscargo[10][0], gamedata.islandscargo[10][1], gamedata.islandscargo[10][2], gamedata.islandscargo[10][3]);
    drawmenuandbox(this_layer, ctx, 0, 7, MENU8ITEMSCNT, x, y, 64, 0, menu7text);
  }
  if(menulayernumber == 8){
    drawmenuandbox(this_layer, ctx, 0, 8, MENU9ITEMSCNT, x, y, 54, 0, " -Back-\n Store:\n Take");
  }
  if(menulayernumber == 9){
    drawmenuandbox(this_layer, ctx, 0, 9, MENU10ITEMSCNT, x, y, 60, 0, " Construct:\n OrderBuy:\n OrderSell:\n -Back-");
  }
  if(menulayernumber == 10){
    int numberofitems = gamedata.numberofplayerships + 1; //only draw the number of slots necessary based on how many player ships there are
    drawmenuandbox(this_layer, ctx, 0, 10, numberofitems, x, y, 54, 0, " -Back-\n Ship1:\n Ship2:\n Ship3:\n Ship4:\n");
  }
  if(menulayernumber == 11){
    drawmenuandbox(this_layer, ctx, 1, 11, MENU12ITEMSCNT, x, y, 52, 2, " SelcIslnd\n 1      2\n 3      4\n 5      6 \n 7      8\n 9      10\n -Back-"); //resource counts
  }
  if(menulayernumber == 12){
    drawmenuandbox(this_layer, ctx, 0, 12, MENU13ITEMSCNT, x, y, 54, 1, " SelcRes\n Metal:\n Stone:\n Wood:\n Food:\n -Back-");
  }
  if(menulayernumber == 13){
    drawmenuandbox(this_layer, ctx, 0, 13, MENU14ITEMSCNT, x, y, 60, 0, " Construct:\n Destruct:\n -Back-"); //should show resources counts while this is open
  }
  if(menulayernumber == 14){
    drawmenuandbox(this_layer, ctx, 0, 14, MENU15ITEMSCNT, x, y, 60, 0, " Withdraw:\n Deposit:\n -Back-"); //should show money when this is open
  }
}

void drawmenuandbox(Layer *this_layer, GContext *ctx, int issquarelayer, int layernumber, int itemscount, int x, int y, int xdiff, int offset, char text[100]){
  itemscount = itemscount + offset;
  GRect layertext;
  GRect highlightbox;
  if(issquarelayer == 0){
    highlightbox = (GRect(x, 2 + y+(gamedata.currentmenu[layernumber] + offset)*15 - gamedata.currentmenu[layernumber], xdiff, 15 )); //highlighting box
    layertext = GRect(x, y, xdiff, 4 + y+(itemscount - 1)*15 - itemscount);
  }
  else if(issquarelayer == 1){ //if you want to draw a number of boxes
    if((gamedata.currentmenu[layernumber]%(itemscount - offset - 1)) == 0 && gamedata.currentmenu[layernumber] != 0){ //draw the last box as large, if number of items is odd
      highlightbox = (GRect(x, 2 + y+((gamedata.currentmenu[layernumber] + offset)/ 2)*15 - (gamedata.currentmenu[layernumber]/2), xdiff, 15 )); //highlighting box
    }
    else if(((gamedata.currentmenu[layernumber] + 1)%2) == 0) //draw box around the second colm of entries
      highlightbox = (GRect(x  + (xdiff/2), 2 + y+((gamedata.currentmenu[layernumber] + offset) / 2)*15 - (gamedata.currentmenu[layernumber]/2), (xdiff / 2), 15 ));
    else if(((gamedata.currentmenu[layernumber] + 1)%2 != 0)) //draw box around the first colm of entires
      highlightbox = (GRect(x, 2 + y+((gamedata.currentmenu[layernumber] + offset) / 2)*15 - (gamedata.currentmenu[layernumber]/2), (xdiff / 2), 15 ));
    layertext = GRect(x, y, xdiff, 4 + y+((itemscount/2 + 1) - 1)*15 - (itemscount/2));
  }
  graphics_fill_rect(ctx, layertext, 0, GCornerNone); //background box
  graphics_draw_rect(ctx, highlightbox); //the box around selected area
  graphics_draw_text(ctx, text, fonts_get_system_font(FONT_KEY_FONT_FALLBACK), layertext, GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
}

void menudownpressproc(){
  
}
void menuuppressproc(){
  
}
void menuselectpressproc(){
  
}
void menubuttonreleaseproc(){
  
}
