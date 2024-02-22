#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <math.h>

using namespace std;

void textRGBA(SDL_Renderer *renderer,int x,int y,string mytext,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num);
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian);
void mainpage(SDL_Renderer *m_renderer,SDL_Event *e);
void endgame(SDL_Renderer *m_renderer,SDL_Event *e);
void aboutus(SDL_Renderer *m_renderer,SDL_Event *e);
void setting(SDL_Renderer *m_renderer,SDL_Event *e);
void playgame(SDL_Renderer *m_renderer,SDL_Event *e);
void newgame(SDL_Renderer *m_renderer,SDL_Event *e);
void stadiumpage(SDL_Renderer *m_renderer,SDL_Event *e);
void recordspage(SDL_Renderer *m_renderer,SDL_Event *e);
int homepage=1,as,cd,endpage=0,aboutpage=0,settingpage=0,playgamepage=0;
int newgamepage=0;
int numberofmusic=1;
int numberofground=1;
int stadium=0;
int recordpage=0;
string gamername1;
string gamername2;
string player1kind="photos\\character11.png";
string player2kind="photos\\character21.png";
string backgroundmusic="musics\\backmusic1.mp3";
string backgroundphoto="photos\\back ground 1.jfif";
string player1name;
string player2name;
int endgoal=5;
string endgoalstr="photos\\endgoal5.png";
int endtime=90;
string endtimestr="photos\\endtime90.png";
int hardness=1;
string hardnessstr="photos\\hardness1.png";
const Uint8* key=SDL_GetKeyboardState(NULL);
int numberofgamers;
bool load=false;
struct playerinformation{
string name;
int game;
int win;
int draw;
int lose;
};
int firstgamercode;
int secondgamercode;
playerinformation arr[100];
int main( int argc, char * argv[] ){
Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO;
Uint32 WND_flags = SDL_WINDOW_SHOWN ;
SDL_Window * m_window;
SDL_Renderer * m_renderer;
SDL_Init( SDL_flags );
SDL_CreateWindowAndRenderer( 1200, 700, WND_flags, &m_window, &m_renderer );
SDL_RaiseWindow(m_window);
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); ///Load background sound
Mix_PlayMusic(GameSound,-1);
TTF_Init();/// use for get name
SDL_Event *e = new SDL_Event();
ifstream fin1("tedad.txt", ios::in);/// get players information with file
fin1>>numberofgamers;
fin1.close();
if(numberofgamers!=0){
ifstream fin2("players.txt", ios::in);/// get players name
for(int i=0;i<numberofgamers;i++){
getline(fin2,arr[i].name);
}
fin2.close();
ifstream fin3("jadval.txt", ios::in);/// get players information with file
for(int i=0;i<numberofgamers;i++){
fin3>>arr[i].game;
fin3>>arr[i].win;
fin3>>arr[i].draw;
fin3>>arr[i].lose;
}
fin3.close();
}
while(endpage==0){///page isn't open while endpage is zero
SDL_Event e;
/// this functions use for different pages
mainpage(m_renderer,&e);
aboutus(m_renderer,&e);
setting(m_renderer,&e);
playgame(m_renderer,&e);
recordspage(m_renderer,&e);
newgame(m_renderer,&e);
endgame(m_renderer,&e);
stadiumpage(m_renderer,&e);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
}
if(endpage==1){///close game and sdl
SDL_DestroyWindow( m_window );
SDL_DestroyRenderer( m_renderer );
Mix_CloseAudio();
IMG_Quit();
SDL_Quit();
TTF_Quit();
return 0;
}
}
void textRGBA(SDL_Renderer *renderer,int x,int y,string mytext,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num){/// use to print string
SDL_Color text_color = { R, G, B, A};
int mWidth = 0;
int mHeight = 0;
SDL_Rect* clip = NULL;
TTF_Font *gFont = NULL;
SDL_Point* center = NULL;

const char * text= mytext.c_str();
SDL_RendererFlip flip;
switch(flip_num){
    case 0:
        flip = SDL_FLIP_NONE;
        break;
    case 1:
        flip = SDL_FLIP_HORIZONTAL;
        break;
    case 2:
        flip = SDL_FLIP_VERTICAL;
        break;
    case 3:
        flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        break;
    default:
        flip = SDL_FLIP_NONE;
}
SDL_Texture* mTexture = NULL;
gFont = TTF_OpenFont(font, font_size);
SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, text_color);
mWidth = textSurface->w;
mHeight = textSurface->h;
mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
SDL_FreeSurface(textSurface);
SDL_Rect renderQuad = {x, y , mWidth, mHeight};
SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
SDL_DestroyTexture(mTexture);
TTF_CloseFont(gFont);
}
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)
{
if(fill_boolian==1)
    filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
if(fill_boolian==0)
    ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);
}
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian)
{
SDL_Rect rectangle ;
rectangle.x = x;
rectangle.y = y;
rectangle.w = w;
rectangle.h = h;
SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
SDL_RenderFillRect(Renderer, &rectangle);
SDL_RenderDrawRect(Renderer, &rectangle);
}
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
int n = addressOfImage.length();
char char_array[n+1];

strcpy(char_array, addressOfImage.c_str());
SDL_Texture *myTexture;
myTexture = IMG_LoadTexture( m_renderer, char_array);
int w1, h1;
SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
SDL_Rect texr1;
texr1.x = xp;
texr1.y = yp;
texr1.w = width;
texr1.h = height;
SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
SDL_DestroyTexture(myTexture);
}
void mainpage(SDL_Renderer *m_renderer,SDL_Event *e){
while(homepage==1){/// page you choose what you want( main page )
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,0,0,"photos\\sound.png",80,80);
texture(m_renderer,0,90,"photos\\high.png",80,80);
texture(m_renderer,0,180,"photos\\medium.png",80,80);
texture(m_renderer,0,270,"photos\\low.png",80,80);
texture(m_renderer,480,50,"photos\\playgame.png",240,135);
texture(m_renderer,480,200,"photos\\setting.png",240,135);
texture(m_renderer,480,350,"photos\\aboutus.png",240,135);
texture(m_renderer,480,500,"photos\\Exit.png",240,135);
SDL_Event e;
if( SDL_PollEvent( &e ) )
if(e.type==SDL_MOUSEBUTTONDOWN){
    if( e.button.button==SDL_BUTTON_LEFT ){
        as=e.motion.x;
        cd=e.motion.y;
        Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
        Mix_PlayChannel(-1,select,0);
    if(as<720 && as>480 && cd>500 &&  cd<635 ){/// open main page
        endpage=1;
        homepage=0;
    }
    if(as<720 && as>480 && cd>350 &&  cd<485 ){/// open about us page
        aboutpage=1;
        homepage=0;
    }
    if(as<720 && as>480 && cd>200 &&  cd<335 ){/// open setting page
        settingpage=1;
        homepage=0;
    }
    if(as<720 && as>480 && cd>50 &&  cd<185 ){/// open play game page
        playgamepage=1;
        homepage=0;
    }
    if(as<80 && as>0 && cd>90 && cd<170){
        Mix_VolumeMusic(128);
    }
    if(as<80 && as>0 && cd>180 && cd<260){
        Mix_VolumeMusic(80);
    }
    if(as<80 && as>0 && cd>270 && cd<350){
        Mix_VolumeMusic(20);
    }
}
}
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
}
}
void endgame(SDL_Renderer *m_renderer,SDL_Event *e)
{
int as,cd;/// as show x of mouse and cd show y of mouse
while(endpage==1){/// open page ask you to close game or not
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,0,0,"photos\\sound.png",80,80);
texture(m_renderer,0,90,"photos\\high.png",80,80);
texture(m_renderer,0,180,"photos\\medium.png",80,80);
texture(m_renderer,0,270,"photos\\low.png",80,80);
texture(m_renderer,480,50,"photos\\playgame.png",240,135);
texture(m_renderer,480,200,"photos\\setting.png",240,135);
texture(m_renderer,480,350,"photos\\aboutus.png",240,135);
texture(m_renderer,480,500,"photos\\Exit.png",240,135);
texture(m_renderer,400,200,"photos\\endgame.bmp",400,300);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
if( SDL_PollEvent( e ) )
    if(e->type==SDL_MOUSEBUTTONDOWN){
        Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
        Mix_PlayChannel(-1,select,0);
        if( e->button.button==SDL_BUTTON_LEFT ){
             as=e->motion.x;
             cd=e->motion.y;
          if(as<580 && as>320 && cd>300 &&  cd<400 ){/// if you choose it game will be close
             endpage=2;
          }
          if(as<780 && as>520 && cd>300 &&  cd<400 ){/// if you choose it game will be continued
             endpage=0;
             homepage=1;
          }
        }
   }
}
SDL_Delay(3);
}
void aboutus(SDL_Renderer *m_renderer,SDL_Event *e){/// it is our about us page
int as,cd;/// as show x of mouse and cd show y of mouse
while(aboutpage==1){/// while it is true you see objects
texture(m_renderer,0,0,"photos\\aboutuspage.png",1200,700);
texture(m_renderer,0,0,"photos\\gohome.png",80,60);
texture(m_renderer,350,180,"photos\\developers.png",200,109);
texture(m_renderer,550,180,"photos\\adimiz.png",493,109);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
if( SDL_PollEvent( e ) )
    if(e->type==SDL_MOUSEBUTTONDOWN){
        Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
        Mix_PlayChannel(-1,select,0);
        if( e->button.button==SDL_BUTTON_LEFT ){
            as=e->motion.x;
            cd=e->motion.y;
            if(as>0 && as<80 && cd>0 && cd<60){///if you choose it main page will opened
                aboutpage=0;
                homepage=1;
            }
        }
    }
}
}
void setting(SDL_Renderer *m_renderer,SDL_Event *e){/// it is setting page to change music and background
int as,cd,i=1;
while(settingpage==1){
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,0,0,"photos\\gohome.png",80,60);
texture(m_renderer,450,100,"photos\\music.png",300,200);
texture(m_renderer,340,170,"photos\\shifticon2.png",60,60);
texture(m_renderer,800,170,"photos\\shifticon1.png",60,60);
texture(m_renderer,450,400,"photos\\theme.png",300,200);
texture(m_renderer,340,470,"photos\\shifticon2.png",60,60);
texture(m_renderer,800,470,"photos\\shifticon1.png",60,60);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
     if( SDL_PollEvent( e ) )
        if(e->type==SDL_MOUSEBUTTONDOWN){
            Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
            Mix_PlayChannel(-1,select,0);
            if( e->button.button==SDL_BUTTON_LEFT ){
               as=e->motion.x;
               cd=e->motion.y;
               if(as>0 && as<80 && cd>0 && cd<60){
                  settingpage=0;
                  homepage=1;
               }
              if(as>340 && as<400 && cd>170 && cd<230){///you could change back ground music
                 numberofmusic--;
                   if(numberofmusic<1){
                        numberofmusic=3;
                   }
                 Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
                 backgroundmusic="musics\\backmusic";
                 backgroundmusic+=to_string(numberofmusic);
                 backgroundmusic+=".mp3";
                 Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); ///Load background sound
                 Mix_PlayMusic(GameSound,-1);
              }
             if(as>800 && as<860 && cd>170 && cd<230){
                 numberofmusic++;
                   if(numberofmusic>3){
                        numberofmusic=1;
                   }
                 Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
                 backgroundmusic="musics\\backmusic";
                 backgroundmusic+=to_string(numberofmusic);
                 backgroundmusic+=".mp3";
                 Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); ///Load background sound
                 Mix_PlayMusic(GameSound,-1);
            }
            if(as>800 && as<860 && cd>470 && cd<530){/// you could change back ground photo

             if(numberofground==1){
                  numberofground=2;
             }
             else if(numberofground==2){
                 numberofground=1;
             }
             backgroundphoto="photos\\back ground ";
             backgroundphoto+=to_string(numberofground);
             backgroundphoto+=".jfif";
             }
             if(as>340 && as<400 && cd>470 && cd<530){/// you could change back ground photo

             if(numberofground==1){
                  numberofground=2;
             }
             else if(numberofground==2){
                 numberofground=1;
             }
             backgroundphoto="photos\\back ground ";
             backgroundphoto+=to_string(numberofground);
             backgroundphoto+=".jfif";
            }
            }
}
}
}
void playgame(SDL_Renderer *m_renderer,SDL_Event *e){/// it is playgame page to choose you play new game or load past one or see records
int as,cd;/// as show x of mouse and cd show y of mouse
while(playgamepage==1){
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,0,0,"photos\\gohome.png",80,60);
texture(m_renderer,450,25,"photos\\new game.png",300,200);
texture(m_renderer,450,250,"photos\\load game.png",300,200);
texture(m_renderer,450,475,"photos\\records.png",300,200);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );
     if( SDL_PollEvent( e ) )
        if(e->type==SDL_MOUSEBUTTONDOWN){
            Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
            Mix_PlayChannel(-1,select,0);
            if( e->button.button==SDL_BUTTON_LEFT ){
               as=e->motion.x;
               cd=e->motion.y;
            if(as>0 && as<80 && cd>0 && cd<60){/// go back to main page
                playgamepage=0;
                homepage=1;
            }
            if(as>450 && as<750 && cd>25 && cd<225){/// get players name
               bool whole=true;
               bool first=true;
               bool second=true;
               string text;
               SDL_Event *event = new SDL_Event();
               while(whole==true){
               SDL_StartTextInput();
               while(first==true){
               if(SDL_PollEvent(event)){
               if(event->type==SDL_TEXTINPUT || event->type==SDL_KEYDOWN){
               system("cls");
               if(event->type==SDL_KEYDOWN && event->key.keysym.sym==SDLK_BACKSPACE && text.length()>0){
               text=text.substr(0,text.length()-1);
               }
               else if(event->type==SDL_TEXTINPUT){
               text+=event->text.text;
               }
               }
               if(event->type==SDL_MOUSEBUTTONDOWN){
                  if( event->button.button==SDL_BUTTON_LEFT){
                    as=event->motion.x;
                    cd=event->motion.y;
                 if(as>900 && as<1000 && cd>500 && cd<550 && text.length()>0){
                     first=false;
                 }
                  }
               }
}
const char *myname=text.c_str();
TTF_Font *font=TTF_OpenFont("font.ttf",40);
SDL_Color color={255,0,0,255};
SDL_Surface *mys= TTF_RenderText_Solid(font,myname,color);
SDL_Texture *matn=SDL_CreateTextureFromSurface(m_renderer,mys);
SDL_Rect matnrect;
matnrect.x=410;
matnrect.y=300;
SDL_QueryTexture(matn,NULL,NULL,&matnrect.w,&matnrect.h);
SDL_FreeSurface(mys);
mys=nullptr;
TTF_CloseFont(font);
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,400,100,"photos\\entername1.png",400,200);
texture(m_renderer,400,300,"photos\\namebox.png",400,50);
texture(m_renderer,900,500,"photos\\next.png",100,50);
SDL_RenderPresent(m_renderer);
SDL_RenderCopy(m_renderer,matn,NULL,&matnrect);
SDL_RenderPresent(m_renderer);
SDL_RenderClear(m_renderer);
if(text.length()==8){
    first=false;
}
}
bool existance=false;
gamername1=text;
for(int i=0;i<numberofgamers;i++){/// check for new player
    if(gamername1==arr[i].name){
        firstgamercode=i;
        existance=true;
    }
}
if(existance==false){///new player
        arr[numberofgamers].name=gamername1;
        arr[numberofgamers].game=0;
        arr[numberofgamers].win=0;
        arr[numberofgamers].draw=0;
        arr[numberofgamers].lose=0;
        firstgamercode=numberofgamers;
        numberofgamers++;
}
text="";
while(second==true){
    if(SDL_PollEvent(event)){
         if(event->type==SDL_TEXTINPUT || event->type==SDL_KEYDOWN){
         system("cls");
         if(event->type==SDL_KEYDOWN && event->key.keysym.sym==SDLK_BACKSPACE && text.length()>0){
             text=text.substr(0,text.length()-1);
         }
         else if(event->type==SDL_TEXTINPUT){
         text+=event->text.text;
         }
         }
         if(event->type==SDL_MOUSEBUTTONDOWN){
             if( e->button.button==SDL_BUTTON_LEFT){
                as=event->motion.x;
                cd=event->motion.y;
                  if(as>900 && as<1000 && cd>500 && cd<550 && text.length()>0){
                      second=false;
                   }
              }
          }
    }
const char *myname=text.c_str();
TTF_Font *font=TTF_OpenFont("font.ttf",40);
SDL_Color color={255,0,0,255};
SDL_Surface *mys= TTF_RenderText_Solid(font,myname,color);
SDL_Texture *matn=SDL_CreateTextureFromSurface(m_renderer,mys);
SDL_Rect matnrect;
matnrect.x=410;
matnrect.y=300;
SDL_QueryTexture(matn,NULL,NULL,&matnrect.w,&matnrect.h);
SDL_FreeSurface(mys);
mys=nullptr;
TTF_CloseFont(font);
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,400,100,"photos\\entername2.png",400,200);
texture(m_renderer,400,300,"photos\\namebox.png",400,50);
texture(m_renderer,900,500,"photos\\next.png",100,50);
SDL_RenderPresent(m_renderer);
SDL_RenderCopy(m_renderer,matn,NULL,&matnrect);
SDL_RenderPresent(m_renderer);
SDL_RenderClear(m_renderer);
if(text.length()==8){
second=false;
}
}
existance=false;
gamername2=text;
    for(int i=0;i<numberofgamers;i++){///check for new player
        if(gamername2==arr[i].name){
            secondgamercode=i;
            existance=true;
        }
        }
        if(existance==false){///new player
            arr[numberofgamers].name=gamername2;
            arr[numberofgamers].game=0;
            arr[numberofgamers].win=0;
            arr[numberofgamers].draw=0;
            arr[numberofgamers].lose=0;
            secondgamercode=numberofgamers;
            numberofgamers++;
       }
whole=false;
}
SDL_StopTextInput();

    ofstream fout1("tedad.txt", ios::out);
             fout1<<numberofgamers<<endl;
    	fout1.close();
    ofstream fout2("players.txt", ios::out);
             for(int i=0;i<numberofgamers;i++){
                fout2<<arr[i].name<<endl;
             }
    	fout2.close();
    ofstream fout3("jadval.txt", ios::out);
             for(int i=0;i<numberofgamers;i++){
                fout3<<arr[i].game<<endl;
                fout3<<arr[i].win<<endl;
                fout3<<arr[i].draw<<endl;
                fout3<<arr[i].lose<<endl;
             }
    	fout3.close();
playgamepage=0;
newgamepage=1;
}
if(as>450 && as<750 && cd>250 && cd<450){///load game page
    playgamepage=0;
    stadium=1;
    load=true;
}
if(as>450 && as<750 && cd>475 && cd<675){///go to records page
playgamepage=0;
recordpage=1;
}
}
}
}
}
void recordspage(SDL_Renderer *m_renderer,SDL_Event *e){
int i=0,as,cd;
while(recordpage==1){/// records are here
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,250,100,"photos\\loadgame.png",700,500);
texture(m_renderer,0,0,"photos\\backpage.png",80,80);
texture(m_renderer,950,100,"photos\\shifticon3.png",80,80);
texture(m_renderer,950,520,"photos\\shifticon4.png",80,80);
textRGBA(m_renderer,255,180,to_string(i+1),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,255,260,to_string(i+2),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,255,340,to_string(i+3),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,255,430,to_string(i+4),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,255,530,to_string(i+5),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,355,180,arr[i].name,"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,355,260,arr[i+1].name,"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,355,340,arr[i+2].name,"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,355,430,arr[i+3].name,"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,355,530,arr[i+4].name,"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,520,180,to_string(arr[i].game),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,520,260,to_string(arr[i+1].game),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,520,340,to_string(arr[i+2].game),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,520,430,to_string(arr[i+3].game),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,520,530,to_string(arr[i+4].game),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,650,180,to_string(arr[i].win),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,650,260,to_string(arr[i+1].win),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,650,340,to_string(arr[i+2].win),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,650,430,to_string(arr[i+3].win),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,650,530,to_string(arr[i+4].win),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,780,180,to_string(arr[i].draw),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,780,260,to_string(arr[i+1].draw),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,780,340,to_string(arr[i+2].draw),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,780,430,to_string(arr[i+3].draw),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,780,530,to_string(arr[i+4].draw),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,900,180,to_string(arr[i].lose),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,900,260,to_string(arr[i+1].lose),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,900,340,to_string(arr[i+2].lose),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,900,430,to_string(arr[i+3].lose),"font.ttf",32,0,0,0,255,0.0,0);
textRGBA(m_renderer,900,530,to_string(arr[i+4].lose),"font.ttf",32,0,0,0,255,0.0,0);
SDL_RenderPresent( m_renderer );
SDL_RenderClear( m_renderer );

        if(SDL_PollEvent(e)){
            if(e->type==SDL_MOUSEBUTTONDOWN){
                Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
                Mix_PlayChannel(-1,select,0);
                if( e->button.button==SDL_BUTTON_LEFT ){
                as=e->motion.x;
                cd=e->motion.y;
                if( as>0 && as<80 && cd>0 && cd<80 ){
                recordpage=0;
                playgamepage=1;
                }
                if( as>950 && as<1030 && cd>100 && cd<180 ){
                    i--;
                }
                if( as>950 && as<1030 && cd>520 && cd<600 ){
                    i++;
                }
                }
            }
        }
if(i>numberofgamers-5){
i=numberofgamers-5;
}
if(i<0){
i=0;
}
}
}
void newgame(SDL_Renderer *m_renderer,SDL_Event *e){

int as,cd,i=1,j=1,k=1;/// as and cd is x and y
player1kind="photos\\character11.png";
player2kind="photos\\character21.png";
while(newgamepage==1){/// you choose new game setting
texture(m_renderer,0,0,backgroundphoto,1200,700);
texture(m_renderer,0,0,"photos\\backpage.png",80,80);
texture(m_renderer,60,250,"photos\\cardback.png",300,200);
texture(m_renderer,840,250,"photos\\cardback.png",300,200);
texture(m_renderer,180,310,player1kind,100,80);
texture(m_renderer,960,310,player2kind,100,80);
texture(m_renderer,330,320,"photos\\shifticon1.png",60,60);
texture(m_renderer,74,320,"photos\\shifticon2.png",60,60);
texture(m_renderer,1110,320,"photos\\shifticon1.png",60,60);
texture(m_renderer,854,320,"photos\\shifticon2.png",60,60);
texture(m_renderer,560,360,"photos\\endgoal.png",80,20);
texture(m_renderer,560,380,endgoalstr,80,80);
texture(m_renderer,640,390,"photos\\shifticon1.png",40,40);
texture(m_renderer,520,390,"photos\\shifticon2.png",40,40);
texture(m_renderer,560,200,"photos\\endtime.png",80,20);
texture(m_renderer,560,220,endtimestr,80,80);
texture(m_renderer,640,230,"photos\\shifticon1.png",40,40);
texture(m_renderer,520,230,"photos\\shifticon2.png",40,40);
texture(m_renderer,560,40,"photos\\hardness.png",80,20);
texture(m_renderer,560,60,hardnessstr,80,80);
texture(m_renderer,640,70,"photos\\shifticon1.png",40,40);
texture(m_renderer,520,70,"photos\\shifticon2.png",40,40);
texture(m_renderer,560,520,"photos\\strat.png",80,80);

    SDL_RenderPresent( m_renderer );
    SDL_RenderClear( m_renderer );
     if( SDL_PollEvent( e ) ){
        if(e->type==SDL_MOUSEBUTTONDOWN){
            Mix_Chunk *select=Mix_LoadWAV("musics\\mouse.wav");
            Mix_PlayChannel(-1,select,0);
            if( e->button.button==SDL_BUTTON_LEFT ){
           as=e->motion.x;
           cd=e->motion.y;
            if(as>0 && as<80 && cd>0 && cd<60){///came back to main page
            newgamepage=0;
            playgamepage=1;
            homepage=0;
            }
            if(as>74 && as<134 && cd>320 && cd<380){///change character 1
                i--;
            if(i<1){
                i=6;
            }
            player1kind="photos\\character1";
            player1kind+=to_string(i);
            player1kind+=".png";
            }
            if(as>330 && as<390 && cd>320 && cd<380){///change character 1
                i++;
            if(i>6){
                i=1;
            }
                player1kind="photos\\character1";
                player1kind+=to_string(i);
                player1kind+=".png";
            }
            if(as>854 && as<914 && cd>320 && cd<380){///change character 2
                j--;
            if(j<1){
                j=6;
            }
            player2kind="photos\\character2";
            player2kind+=to_string(j);
            player2kind+=".png";
}
            if(as>1110 && as<1170 && cd>320 && cd<380){///change character 2
                j++;
            if(j>6){
                j=1;
            }
            player2kind="photos\\character2";
            player2kind+=to_string(j);
            player2kind+=".png";
            }
            if(as>520 && as<560 && cd>390 && cd<430){///choose end goal
                endgoal--;
            if(endgoal<1){
                endgoal=5;
            }
            endgoalstr="photos\\endgoal";
            endgoalstr+=to_string(endgoal);
            endgoalstr+=".png";
            }
            if(as>640 && as<680 && cd>390 && cd<430){///choose end goal
                endgoal++;
            if(endgoal>5){
                endgoal=1;
            }
            endgoalstr="photos\\endgoal";
            endgoalstr+=to_string(endgoal);
            endgoalstr+=".png";
            }
            if(as>520 && as<560 && cd>230 && cd<270){///choose end time
            endtime-=30;
            if(endtime<1){
            endtime=90;
            }
            endtimestr="photos\\endtime";
            endtimestr+=to_string(endtime);
            endtimestr+=".png";
            }
            if(as>640 && as<680 && cd>230 && cd<270){///choose end time
            endtime+=30;
            if(endtime>90){
            endtime=30;
            }
            endtimestr="photos\\endtime";
            endtimestr+=to_string(endtime);
            endtimestr+=".png";
            }
            if(as>520 && as<560 && cd>70 && cd<110){///choose hardness
                hardness--;
            if(hardness<1){
                hardness=3;
            }
            hardnessstr="photos\\hardness";
            hardnessstr+=to_string(hardness);
            hardnessstr+=".png";
            }
            if(as>640 && as<680 && cd>70 && cd<110){///choose hardness
                hardness++;
            if(hardness>3){
                hardness=1;
            }
            hardnessstr="photos\\hardness";
            hardnessstr+=to_string(hardness);
            hardnessstr+=".png";
            }
if(as>560 && as<640 && cd>520 && cd<600){///start game
newgamepage=0;
stadium=1;
}
}
}
}
}
}
void stadiumpage(SDL_Renderer *m_renderer,SDL_Event *e){/// where you start playing
int i=2;
const Uint8* key=SDL_GetKeyboardState(NULL);
bool running=true;/// it is for page before game
int waiter=0;
bool runner=true;/// it is for stadiom
while(stadium==1){
while(running==true){
texture(m_renderer,0,0,"photos\\waiting.jpg",1200,700);
texture(m_renderer,350,445,"photos\\toolbar.png",500,100);
waiter++;/// it should pass
///blank filling:
if(waiter>10){
texture(m_renderer,360,460,"photos\\ball.png",55,55);
}
if(waiter>20){
texture(m_renderer,400,460,"photos\\ball.png",55,55);
}
if(waiter>30){
texture(m_renderer,440,460,"photos\\ball.png",55,55);
}
if(waiter>40){
texture(m_renderer,480,460,"photos\\ball.png",55,55);
}
if(waiter>50){
texture(m_renderer,520,460,"photos\\ball.png",55,55);
}
if(waiter>60){
texture(m_renderer,560,460,"photos\\ball.png",55,55);
}
if(waiter>70){
texture(m_renderer,600,460,"photos\\ball.png",55,55);
}
if(waiter>80){
texture(m_renderer,640,460,"photos\\ball.png",55,55);
}
if(waiter>90){
texture(m_renderer,680,460,"photos\\ball.png",55,55);
}
if(waiter>100){
texture(m_renderer,720,460,"photos\\ball.png",55,55);
}
if(waiter>110){
texture(m_renderer,760,460,"photos\\ball.png",55,55);
}
if(waiter>120){
texture(m_renderer,800,460,"photos\\ball.png",55,55);
}
/// amount of delay:
if(waiter<40){
SDL_Delay(20);
}
if(waiter>40 && waiter<80){
SDL_Delay(40);
}
if(waiter>80 && waiter<100){
SDL_Delay(150);
}
if(waiter>100){
SDL_Delay(10);
}
if(waiter>125){
texture(m_renderer,350 ,580,"photos\\press.png",576,100);
          if( SDL_PollEvent( e ) ){
             if(e->type==SDL_KEYDOWN){
                running=false;
             }
          }
             waiter=130;
        }
         SDL_RenderPresent( m_renderer );
         SDL_RenderClear( m_renderer );
}
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);///stadium fans
string temp=backgroundmusic;
backgroundmusic="musics\\mus.mp3";
Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); ///Load background sound
Mix_PlayMusic(GameSound,-1);
const Uint8* keystate=SDL_GetKeyboardState(NULL);
double xball=580;/// x of ball
double yball=300;/// y of ball
double xplay1=200;/// x of player 1
double yplay1=520;/// y of player 1
double xplay2=1000;/// x of player 2
double yplay2=520;/// y of player 2
double powplay1=0;///power
double powplay2=0;///power
double vxball=0;/// velocity of ball in x direction
double vyball=0;/// velocity of ball in y direction
double vyplay1=0;/// velocity of player 1 in y direction
double vyplay2=0;/// velocity of player 2 in y direction
double geranesh=0.5;/// it is g
double ayball=0.5;/// it is acceleration of ball in y direction
double axball=0.01;/// it is acceleration of ball in y direction
int goal1=0;/// number of player 1 goal
int goal2=0;/// number of player 2 goal
string stock1="photos\\stock11.png";/// foot player 1
string stock2="photos\\stock21.png";/// foot player 2
bool shooted1=false;/// it shows player 1 has shooted ball or not
bool shooted2=false;/// it shows player 2 has shooted ball or not
int now=0;/// use for show present time
int previous=SDL_GetTicks();/// use for show past time
int boardtime=endtime;///it show in c=score board
bool stoppage=false;/// show you had stopped game or not
int as ,cd;/// x and y
bool kikbal1=false;/// it show that you shoot ball in kick fire ball power
bool kikbal2=false;/// it show that you shoot ball in kick fire ball power
int deadtime1=0;/// player couldn't play for this time
int deadtime2=0;/// player couldn't play for this time
bool dead1;/// it show he is dead or not
bool dead2;/// it show he is dead or not
int birdnumber=1;///birds
int birdsymbol=1;///birds
string bird;///birds
bool combat1=false;/// combat power
bool combat2=false;///combat power
bool invisball=false;///invisible power
int invistime=0;///invisible power
bool fire1=false;/// head fire ball
bool fire2=false;/// head fire ball
bool tripple1=false;/// tripple clone
bool tripple2=false;/// tripple clone
int triptime1=0;/// tripple clone
int triptime2=0;/// tripple clone
double xtripfirst1=xplay1-200;/// tripple clone
double xtripfirst2=xplay1-400;/// tripple clone
double ytripfirst1=yplay1;/// tripple clone
double ytripfirst2=yplay1;/// tripple clone
double xtripsecond1=xplay2+200;/// tripple clone
double xtripsecond2=xplay2+400;/// tripple clone
double ytripsecond1=yplay2;/// tripple clone
double ytripsecond2=yplay2;/// tripple clone
string stadiumfan;/// it use to show fans
int fannumber=1;/// for show fans animated
string myball;/// show many visual ball kind
int ballnumber=1;/// ball kind
bool ghost1=false;/// ghost ball power player1
bool ghost2=false;/// ghost ball power player2
int ghosttime1=0;/// show its time
int ghosttime2=0;///show its time
bool theif1=false;/// theif power player1
bool theif2=false;/// theif power player1
int r=0;///use to find random of power in theif
bool cheat=false;///it show you had cheat or not
int cheattime=0;/// it is cheat dead line
int cheatchance=1;/// times you could cheat
int cheatamountball=0;/// your ball radius increase
int cheatamountother=0;/// radius
bool prize1=true;///prize
bool prize2=true;///prize
bool prize3=true;///prize
if(load==true){/// if you want to load game you should get information
    ifstream fin("save.txt",ios::in);
getline(fin,gamername1);
getline(fin,gamername2);
fin>>player1kind;
fin>>player2kind;
fin>>backgroundmusic;
fin>>endgoal;
fin>>endtime;
fin>>hardness;
fin>>firstgamercode;
fin>>secondgamercode;
fin>>xball;
fin>>yball;
fin>>xplay1;
fin>>yplay1;
fin>>xplay2;
fin>>yplay2;
fin>>powplay1;
fin>>powplay2;
fin>>vxball;
fin>>vyball;
fin>>vyplay1;
fin>>vyplay2;
fin>>geranesh;
fin>>ayball;
fin>>axball;
fin>>goal1;
fin>>goal2;
fin>>stock1;
fin>>stock2;
fin>>shooted1;
fin>>shooted2;
fin>>boardtime;
fin>>kikbal1;
fin>>kikbal2;
fin>>deadtime1;
fin>>deadtime2;
fin>>dead1;
fin>>dead2;
fin>>birdnumber;
fin>>birdsymbol;
fin>>combat1;
fin>>combat2;
fin>>invisball;
fin>>invistime;
fin>>fire1;
fin>>fire2;
fin>>tripple1;
fin>>tripple2;
fin>>triptime1;
fin>>triptime2;
fin>>xtripfirst1;
fin>>xtripfirst2;
fin>>ytripfirst1;
fin>>ytripfirst2;
fin>>xtripsecond1;
fin>>xtripsecond2;
fin>>ytripsecond1;
fin>>ytripsecond2;
fin>>stadiumfan;
fin>>fannumber;
fin>>myball;
fin>>ballnumber;
fin>>ghost1;
fin>>ghost2;
fin>>ghosttime1;
fin>>ghosttime2;
fin>>theif1;
fin>>theif2;
fin>>r;
fin>>cheat;
fin>>cheattime;
fin>>cheatchance;
fin>>cheatamountball;
fin>>cheatamountother;
fin>>prize1;
fin>>prize2;
fin>>prize3;
fin.close();
load=false;
}
        Mix_Chunk *soot=Mix_LoadWAV("musics\\soot1.wav");/// chunk
        Mix_PlayChannel(-1,soot,0);
    while(runner==true){/// it will be true while time finished or one player reach the goal limit
    texture(m_renderer,0,0,stadiumfan,1200,700);/// back ground  "photos\\stadiom.png"
    if(hardness==1 && invisball==false){/// hardness 1
    texture(m_renderer,xball,yball,myball,40+cheatamountball,40+cheatamountball);
    }
    if(hardness==2 && invisball==false){///hardness 2 you see ball one second and not
        if(boardtime%2==0)
    texture(m_renderer,xball,yball,myball,40+cheatamountball,40+cheatamountball);
    }
    if(hardness==3 && invisball==false){/// you see ball saye
    ellipse(m_renderer,xball+20,624,10+(yball-480)/10,10,50-(yball-480)/2,50-(yball-480)/2,50-(yball-480)/2,1);
    }
    texture(m_renderer,xplay1,yplay1,player1kind,80,80);///player 1
    texture(m_renderer,xplay2,yplay2,player2kind,80,80);/// player 2
    texture(m_renderer,xplay1+40,yplay1+60,stock1,100,50);///foot 1
    texture(m_renderer,xplay2-60,yplay2+60,stock2,100,50);/// foot 2
    if(tripple1==true){/// tripple clone firs player
        texture(m_renderer,xtripfirst1,ytripfirst1,player1kind,80,80);
        texture(m_renderer,xtripfirst2,ytripfirst2,player1kind,80,80);
        texture(m_renderer,xtripfirst1+40,ytripfirst1+60,stock1,100,50);
        texture(m_renderer,xtripfirst2+40,ytripfirst1+60,stock1,100,50);

    }
    if(tripple2==true){/// tripple clone second player
        texture(m_renderer,xtripsecond1,ytripsecond1,player2kind,80,80);
        texture(m_renderer,xtripsecond2,ytripsecond2,player2kind,80,80);
        texture(m_renderer,xtripsecond1-60,ytripsecond1+60,stock2,100,50);
        texture(m_renderer,xtripsecond2-60,ytripsecond2+60,stock2,100,50);
    }
    texture(m_renderer,0,420,"photos\\darvaz1.png",75,200);///gate 1
    texture(m_renderer,1125,420,"photos\\darvaz2.png",75,200);///gate 2
    if(combat1==true){/// it is boxing glove for combat power
    texture(m_renderer,xplay1+80,yplay1+20,"photos\\boxing2.png",160,50);
    }
    if(combat2==true){/// it is boxing glove for combat power
    texture(m_renderer,xplay2-160,yplay2+20,"photos\\boxing1.png",160,50);
    }
    textRGBA(m_renderer,10,80,gamername1,"font.ttf",32,0,0,0,255,0.0,0);///name
    textRGBA(m_renderer,1080,80,gamername2,"font.ttf",32,0,0,0,255,0.0,0);///name
    textRGBA(m_renderer,520,30,to_string(goal1),"font.ttf",48,0,0,0,255,0.0,0);///goal
    textRGBA(m_renderer,670,30,to_string(goal2),"font.ttf",48,0,0,0,255,0.0,0);///goal
    textRGBA(m_renderer,570,100,to_string(boardtime),"font.ttf",48,0,0,0,255,0.0,0);///time
    rect(m_renderer, 5,30,powplay1,50,255, 0, 0, 1);///power
    rect(m_renderer, 1195-powplay2,30,powplay2,50,0, 0, 255, 1);///power
    if(deadtime2>0){/// birds flying
            birdnumber+=birdsymbol;
            bird="photos\\bird";
            bird+=to_string(birdnumber);
            bird+=".png";
            texture(m_renderer,xplay2+15+(birdnumber-8)*5,yplay2,bird,60,60);
    if(birdnumber==8){
        birdnumber=16;
        birdsymbol*=-1;
    }
    if(birdnumber==9){
        birdnumber=1;
        birdsymbol*=-1;
    }
    }
    if(deadtime1>0){/// birds flying
            birdnumber+=birdsymbol;
            bird="photos\\bird";
            bird+=to_string(birdnumber);
            bird+=".png";
            texture(m_renderer,xplay1+15+(birdnumber-8)*5,yplay1,bird,60,60);
    if(birdnumber==8){
        birdnumber=16;
        birdsymbol*=-1;
    }
    if(birdnumber==9){
        birdnumber=1;
        birdsymbol*=-1;
    }
    }
    if(boardtime<80 && boardtime>70 && prize3==true ){/// prize 3 increase your cheat chance
    texture(m_renderer,560,480,"photos\\prize3.png",80,80);
    if(xball>530 && xball<630 && yball<550 && yball>450){
        cheatchance++;
        prize3=false;
    }
}
    if(boardtime<60 && boardtime>45 && prize2==true){/// prize 2 give you power
    texture(m_renderer,560,480,"photos\\prize2.png",80,80);
    if(xball>530 && xball<630 && yball<550 && yball>450 && vxball>0){
        powplay1+=50;
        prize2=false;
    }
    if(xball>530 && xball<630 && yball<550 && yball>450 && vxball<0){
        powplay2+=50;
        prize2=false;
    }
    }
    if(boardtime<30 && boardtime>20 && prize1==true){/// increase 1 goal
    texture(m_renderer,560,480,"photos\\prize1.png",80,80);
    if(xball>530 && xball<630 && yball<550 && yball>450 && vxball>0){
        goal1++;
        prize1=false;
    }
    if(xball>530 && xball<630 && yball<550 && yball>450 && vxball<0){
        goal2++;
        prize1=false;
    }
    }

        SDL_RenderPresent( m_renderer );
    if(combat1==true || combat2==true){/// made delay to see glove
        SDL_Delay(500);
        combat1=false;
        combat2=false;
    }
        SDL_RenderClear( m_renderer );

stadiumfan="photos\\stadiom";/// animated fans
stadiumfan+=to_string(fannumber);
stadiumfan+=".png";
myball="photos\\ball";
myball+=to_string(ballnumber);
myball+=".png";
if(vxball>0){/// animated ball
    ballnumber++;
}
if(vxball<0){
    ballnumber--;
}
if(ballnumber<1){
    ballnumber=4;
}
if(ballnumber>4){
    ballnumber=1;
}///animated ball
xball+=vxball;/// change x and y
yball+=vyball;
vyball+=ayball;
yplay1+=vyplay1;
yplay2+=vyplay2;
vyplay1+=geranesh;
vyplay2+=geranesh;
powplay1+=1;///powers filling
powplay2+=1;
xtripfirst1=xplay1-200;/// if triple was true
xtripfirst2=xplay1-400;
ytripfirst1=yplay1;
ytripfirst2=yplay1;
xtripsecond1=xplay2+200;
xtripsecond2=xplay2+400;
ytripsecond1=yplay2;
ytripsecond2=yplay2;
now=SDL_GetTicks();/// use to show time and dead lines
if(now>previous+1000){
    boardtime--;
    previous=now;
    if(deadtime2>0){
        deadtime2--;
    }
    if(deadtime1>0){
        deadtime1--;
    }
    if(invistime>0){
        invistime--;
    }
    if(triptime1>0){
        triptime1--;
    }
    if(triptime2>0){
        triptime2--;
    }
    if(ghosttime1>0){
        ghosttime1--;
    }
    if(ghosttime2>0){
        ghosttime2--;
    }
    if(cheattime>0){
        cheattime--;
    }
fannumber++;
if(fannumber==7){
    fannumber=1;
}

}
if(vxball>0){///estekak horizontal
    vxball-=axball;
}

if(vxball<0){///estekak horizontal
    vxball+=axball;
}

if(vxball<0.03 && vxball>-0.03){///vxball=0
    vxball=0;
}
if(xball>-200 && xball<25 && yball>410 && yball<582){///goal player2
    goal2++;
    xball=600;
    yball=300;
    vxball=0;
    vyball=0;
    powplay1+=80;
        kikbal1=false;
        kikbal2=false;
        invisball=false;
        invistime=0;
        dead1=false;
        dead2=false;
        deadtime1=0;
        deadtime2=0;
        fire1=false;
        fire2=false;
        Mix_Chunk *goalsound=Mix_LoadWAV("musics\\goal.WAV");
        Mix_PlayChannel(-1,goalsound,0);
    SDL_Delay(500);
}
if(xball>1140 && xball<1400 && yball>410 && yball<582){///goal player1
    goal1++;
    xball=600;
    yball=300;
    vxball=0;
    vyball=0;
    powplay2+=80;
        kikbal1=false;
        kikbal2=false;
        invisball=false;
        invistime=0;
        dead1=false;
        dead2=false;
        deadtime1=0;
        deadtime2=0;
        fire1=false;
        fire2=false;
        Mix_Chunk *goalsound=Mix_LoadWAV("musics\\goal.WAV");
        Mix_PlayChannel(-1,goalsound,0);
    SDL_Delay(500);
}
if( (xball<0 || xball>1180-cheatamountother) && yball<390-cheatamountother  ){/// touch out walls
    vxball*=-1;
if(xball<0){
    xball=0;
}
if(xball>1180-cheatamountother){
    xball=1180-cheatamountother;
}
    if(kikbal2==true){
        kikbal2=false;
    }
    if(kikbal1==true){
        kikbal1=false;
    }
    if(fire1==true){
        fire1=false;
    }
    if(fire2==true){
        fire2=false;
    }
xball+=vxball;
}

if(yball<0 || yball>580-cheatamountother){///touch field

    vyball*=-0.7;
    if(yball>580-cheatamountother){
    yball=581-cheatamountother;
    }
    else{
        yball=0;
    }
    if(vyball<0.3 && vyball>-0.3){
        vyball=0;
    }
    if(vyball<-1){
      Mix_Chunk *fieldtoch=Mix_LoadWAV("musics\\field.wav");
      Mix_PlayChannel(-1,fieldtoch,0);
     }
}
if(xball>xplay1 && xball-xplay1<70 && yball>yplay1 && yball<yplay1+81 && ghost2==false){///touch front player1
    xball=xplay1+71;
    vxball*=-1;
    xball+=vxball;
    if(kikbal2==true){
        deadtime1=3;
        dead1=true;
        kikbal2=false;
        xplay1-=200;
    }
    if(fire2==true){
        xplay2-=200;
        fire2=false;
    }
}
if(yplay1>yball && yplay1-yball<40+cheatamountother && xball>=xplay1 && xball<=xplay1+60 && ghost2==false){///touch head player1
    vyball*=-0.8;
    if(xball>=xplay1+40 && xball<=xplay1+60 && vxball<0){
        vxball*=-1;
    }
yball+=vyball;
xball+=vxball;
    if(kikbal2==true){
        deadtime1=3;
        dead1=true;
        kikbal2=false;
        xplay1-=200;
    }
    if(fire2==true){
        deadtime1=3;
        dead1=true;
        fire2=false;
    }
}
if(xplay1>xball && xplay1-xball<35+cheatamountother &&yball>yplay1 && yball<yplay1+81 && ghost2==false){///touch back player1
    xball=xplay1-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
}
if(xplay2>xball && xplay2-xball<35+cheatamountother && yball>yplay2 && yball<yplay2+81 && ghost1==false){///touch front player2
    xball=xplay2-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
    if(kikbal1==true){
        deadtime2=3;
        dead2=true;
        kikbal1=false;
        xplay2+=200;
    }
    if(fire1==true){
        xplay2+=200;
        fire1=false;
    }
}
if(yplay2>yball && yplay2-yball<40+cheatamountother && xball>=xplay2-cheatamountother && xball<=xplay2+60 && ghost1==false){///touch head player2
    vyball*=-0.8;
    if(xball>=xplay2 && xball<=xplay2+20 && vxball>0){
        vxball*=-1;
    }
    if(kikbal1==true){
        deadtime2=3;
        dead2=true;
        kikbal1=false;
        xplay2+=200;
    }
    if(fire1==true){
        deadtime2=3;
        dead2=true;
        fire1=false;
    }
    yball+=vyball;
    xball+=vxball;
}
if(xball>xplay2 && xball-xplay2<80 && yball>yplay2 && yball<yplay2+81 && ghost1==false){///touch back player2
    xball=xplay2+71;
    vxball*=-1;
    xball+=vxball;
}
if(xball>0 && xball<65 && yball>380-cheatamountother && yball<410-cheatamountother){///touch up pf tirak 1
    vyball*=-0.8;
    yball=380-cheatamountother;
Mix_Chunk *tiraksound=Mix_LoadWAV("musics\\ti.WAV");
Mix_PlayChannel(-1,tiraksound,0);
}
if(xball>1095-cheatamountother && xball<1200 && yball>380-cheatamountother && yball<410-cheatamountother){/// touch up of tirak 2
    vyball*=-0.8;
    yball=380;
Mix_Chunk *tiraksound=Mix_LoadWAV("musics\\ti.WAV");
Mix_PlayChannel(-1,tiraksound,0);
}
if(xball>65 && xball<75 && yball>380-cheatamountother && yball<425-cheatamountother){/// touch front tirak 1
    xball=76;
    if(vxball<0){
    vxball*=-1;
    }
    if(kikbal2==true){
        kikbal2=false;
    }
Mix_Chunk *tiraksound=Mix_LoadWAV("musics\\ti.WAV");
Mix_PlayChannel(-1,tiraksound,0);
}
if(xball>1088-cheatamountother && xball<1100-cheatamountother && yball>380-cheatamountother && yball<430-cheatamountother){///touch front tirak 2
    xball=1079-cheatamountother;
if(vxball>0){
    vxball*=-1;
}
    if(kikbal1==true){
        kikbal1=false;
    }
Mix_Chunk *tiraksound=Mix_LoadWAV("musics\\ti.WAV");
Mix_PlayChannel(-1,tiraksound,0);
}
if(yplay1>519){/// touch player 1 with field after jump
    vyplay1*=-0.7;
    yplay1=520;
    if(vyplay1<3 && vyplay1>-3){
        vyplay1=0;
    }
}
if(yplay2>519){/// touch player 2 with field after jump
    vyplay2*=-0.7;
    yplay2=520;
    if(vyplay2<2 && vyplay2>-2){
        vyplay2=0;
    }
}

if(tripple1==true){

if(xball>xtripfirst1 && xball-xtripfirst1<70 && yball>ytripfirst1 && yball<ytripfirst1+81 && ghost2==false){///touch front trip 1
    xball=xtripfirst1+71;
    vxball*=-1;
    xball+=vxball;

}
if(ytripfirst1>yball && ytripfirst1-yball<40+cheatamountother && xball>=xtripfirst1 && xball<=xtripfirst1+60  && ghost2==false){///touch head trip 1
    vyball*=-0.8;
    if(xball>=xtripfirst1+40 && xball<=xtripfirst1+60 && vxball<0){
        vxball*=-1;
    }
yball+=vyball;
xball+=vxball;

}
if(xtripfirst1>xball && xtripfirst1-xball<35+cheatamountother &&yball>ytripfirst1 && yball<ytripfirst1+81  && ghost2==false){///touch back trip 1
    xball=xtripfirst1-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
}

if(xball>xtripfirst2 && xball-xtripfirst2<70 && yball>ytripfirst2 && yball<ytripfirst2+81 && ghost2==false){///touch front trip 2
    xball=xtripfirst2+71;
    vxball*=-1;
    xball+=vxball;

}
if(ytripfirst2>yball && ytripfirst2-yball<40+cheatamountother && xball>=xtripfirst2 && xball<=xtripfirst2+60 && ghost2==false){///touch head trip 2
    vyball*=-0.8;
    if(xball>=xtripfirst2+40 && xball<=xtripfirst2+60 && vxball<0){
        vxball*=-1;
    }
yball+=vyball;
xball+=vxball;

}
if(xtripfirst2>xball && xtripfirst2-xball<35+cheatamountother && yball>ytripfirst2 && yball<ytripfirst2+81  && ghost2==false){///touch back trip 2
    xball=xtripfirst2-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
}

}

if(tripple2==true){
if(xtripsecond1>xball && xtripsecond1-xball<35+cheatamountother && yball>ytripsecond1 && yball<ytripsecond1+81 && ghost1==false){///touch front trip 1
    xball=xtripsecond1-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
}
if(ytripsecond1>yball && ytripsecond1-yball<40+cheatamountother && xball>=xtripsecond1-cheatamountother && xball<=xtripsecond1+60 && ghost1==false){///touch head trip 1
    vyball*=-0.8;
    if(xball>=xtripsecond1 && xball<=xtripsecond1+20 && vxball>0){

        vxball*=-1;
    }
    yball+=vyball;
    xball+=vxball;
}
if(xball>xtripsecond1 && xball-xtripsecond1<80 && yball>ytripsecond1 && yball<ytripsecond1+81 && ghost1==false){///touch back trip 1
    xball=xtripsecond1+71;
    vxball*=-1;
    xball+=vxball;
}
if(xtripsecond2>xball && xtripsecond2-xball<35+cheatamountother && yball>ytripsecond2 && yball<ytripsecond2+81 && ghost1==false){///touch front trip 2
    xball=xtripsecond2-36-cheatamountother;
    vxball*=-1;
    xball+=vxball;
}
if(ytripsecond2>yball && ytripsecond2-yball<40+cheatamountother && xball>=xtripsecond2-cheatamountother && xball<=xtripsecond2+60 && ghost1==false){///touch head trip 2
    vyball*=-0.8;
    if(xball>=xtripsecond2 && xball<=xtripsecond2+20 && vxball>0){

        vxball*=-1;
    }
    yball+=vyball;
    xball+=vxball;
}
if(xball>xtripsecond2 && xball-xtripsecond2<80 && yball>ytripsecond2 && yball<ytripsecond2+81 && ghost1==false){///touch back trip 2
    xball=xtripsecond2+71;
    vxball*=-1;
    xball+=vxball;
}
}

if(xplay1<0){/// you couldn't exit stadium
    xplay1=0;
}
if(xplay2>1120){
    xplay2=1120;
}
if(powplay1>495){/// powers are full
    powplay1=496;
}
if(powplay2>495){
    powplay2=496;
}
if(stock1=="photos\\stock12.png"){/// stocks
    stock1="photos\\stock11.png";
}
if(stock2=="photos\\stock22.png"){
    stock2="photos\\stock21.png";
}
if(deadtime2==0){/// dead lines
    dead2=false;
}
if(deadtime1==0){
    dead1=false;
}
if(invistime==0){
    invisball=false;
}
if(triptime1==0){
    tripple1=false;
}
if(triptime2==0){
    tripple2=false;
}
if(ghosttime1==0){
    ghost1=false;
}
if(ghosttime2==0){
    ghost2=false;
}
if(cheattime==0){
    cheat=false;
    cheatamountball=0;
    cheatamountother=0;
}
if( SDL_PollEvent( e ) ){/// use for power shoot change place jump and...
if(e->type==SDL_MOUSEBUTTONDOWN){/// stop game
        SDL_GetMouseState(&as,&cd);
    if( as>520 && as<680 && cd>0 && cd<80){
        stoppage=true;
    }
}
if(e->type==SDL_KEYDOWN){
if(keystate[SDL_SCANCODE_B] && cheatchance!=0){/// cheat
    cheat=true;
    cheatchance--;
    cheattime=10;
    cheatamountball=40;
    cheatamountother=35;
}

if(keystate[SDL_SCANCODE_W] && yplay1>515 && dead1==false){/// jump 1
    vyplay1=10;
}
if(keystate[SDL_SCANCODE_A] && dead1==false){/// left 1
    xplay1-=10;
}
if(keystate[SDL_SCANCODE_D] && dead1==false){/// right 1
    xplay1+=10;
}
if(keystate[SDL_SCANCODE_S] && dead1==false){/// shoot

    if(xball>=xplay1+10 && xball<=xplay1+100 && yball>=yplay1+25-cheatamountother && yball<=yplay1+70 && ghost2==false){///shoot normal
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock1="photos\\stock12.png";
    if(shooted1==false && xball>=xplay1+110 && xball<=xplay1+120 && yball>=yplay1+55 && yball<=yplay1+70 && ghost2==false){/// shoot under foot
     vxball=+12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xplay1+100 && xball<=xplay1+120 && yball>=yplay1+30-cheatamountother && yball<yplay1+55 && ghost2==false){/// shoot front of foot
        vxball=+12;
        vyball=-8;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xplay1+70 && xball<xplay1+100 && yball>=yplay1+30-cheatamountother && yball<yplay1+55 && ghost2==false){/// shoot up of foot
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
shooted1=false;
    if(tripple1==true){
            if(xball>=xtripfirst1+10 && xball<=xtripfirst1+100 && yball>=ytripfirst1+25-cheatamountother && yball<=ytripfirst1+70 && ghost2==false){///shoot normal trip 1
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock1="photos\\stock12.png";
    if(shooted1==false && xball>=xtripfirst1+110 && xball<=xtripfirst1+120 && yball>=ytripfirst1+55 && yball<=ytripfirst1+70  && ghost2==false){/// shoot under foot trip 1
     vxball=+12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xtripfirst1+100 && xball<=xtripfirst1+120 && yball>=ytripfirst1+30-cheatamountother && yball<ytripfirst1+55 && ghost2==false){/// shoot front of foot trip 1
        vxball=+12;
        vyball=-8;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xtripfirst1+70 && xball<xtripfirst1+100 && yball>=ytripfirst1+30-cheatamountother && yball<ytripfirst1+55 && ghost2==false){/// shoot up of foot trip 1
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
shooted1=false;
            if(xball>=xtripfirst2+10 && xball<=xtripfirst2+100 && yball>=ytripfirst2+25-cheatamountother && yball<=ytripfirst2+70 && ghost2==false){///shoot normal trip 2
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock1="photos\\stock12.png";
    if(shooted1==false && xball>=xtripfirst2+110 && xball<=xtripfirst2+120 && yball>=ytripfirst2+55 && yball<=ytripfirst2+70  && ghost2==false){/// shoot under foot trip 2
     vxball=+12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xtripfirst2+100 && xball<=xtripfirst2+120 && yball>=ytripfirst2+30-cheatamountother && yball<ytripfirst2+55 && ghost2==false){/// shoot front of foot trip 2
        vxball=+12;
        vyball=-8;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    if(shooted1==false && xball>=xtripfirst2+70 && xball<xtripfirst2+100 && yball>=ytripfirst2+30-cheatamountother && yball<ytripfirst2+55 && ghost2==false){/// shoot up of foot trip 2
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted1=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
shooted1=false;
    }
}
if(keystate[SDL_SCANCODE_Q]){/// theif power
    theif1=true;
    r=rand()%6;
}
if((keystate[SDL_SCANCODE_X] || theif1==true) && powplay1>490 && dead1==false && ghost2==false){/// other powers
    powplay1=0;

    if(  player1kind=="photos\\character11.png"  || (theif1==true && r==0)){
    stock1="photos\\stock12.png";
    if(xball>=xplay1+10 && xball<=xplay1+100 && yball>=yplay1+25-cheatamountother && yball<=yplay1+70 && ghost2==false){///kick fire ball
        vxball=25;
        kikbal1=true;
    }
    }
    if(player1kind=="photos\\character12.png"  || (theif1==true && r==1) ){/// combat power
        combat1=true;
        if(xplay2-xplay1<240){
            dead2=true;
            deadtime2=4;
        }
    }
    if(player1kind=="photos\\character13.png"  || (theif1==true && r==2)){/// invisible ball
        if( xplay1<xball && xball-xplay1<120 && yball>480 && yball<582 && ghost2==false){
            stock1="photos\\stock12.png";
            invisball=true;
            invistime=4;
            vxball=+10;
            vyball=-10;
        }
    }
    if(player1kind=="photos\\character14.png"  || (theif1==true && r==3)){///head fir ball
        if(xball>xplay1 && xball-xplay1<110 && yball<510 && yball>400-cheatamountother && ghost2==false){
            yball-=40;
            yplay1=yball;
            xball=xplay1+90;
        if( asin(200/ ((1150-xball)*2*3.14) )<=(3.14/4)){
            vxball=35;
            vyball=0;
        }
        else{
            vxball=30;
            vyball=-10;
        }
        fire1=true;
        }
    }
    if(  (player1kind=="photos\\character15.png"  || (theif1==true && r==4)) && xplay2>500  ){/// triple
        tripple1=true;
        triptime1=8;
    }
    if( (player1kind=="photos\\character15.png"  || (theif1==true && r==4) ) && xplay2<500){
        powplay1=496;
    }
    if(player1kind=="photos\\character16.png"  || (theif1==true && r==5)){/// ghost ball
        ghost1=true;
        ghosttime1=8;
    }
    theif1=false;
}
if(keystate[SDL_SCANCODE_I] && yplay2>515 && dead2==false){/// jump 2
    vyplay2=10;
}
if(keystate[SDL_SCANCODE_J] &&xplay2-xplay1>180 && dead2==false){///go left 2
    xplay2-=10;
}
if(keystate[SDL_SCANCODE_L] && dead2==false){/// right 2
    xplay2+=10;
}
if(keystate[SDL_SCANCODE_K] && dead2==false){/// shoot 2
    if(xball>=xplay2-80-cheatamountother && xball<=xplay2-20 && yball>=yplay2+25-cheatamountother && yball<=yplay2+70  && ghost1==false){//shoot normal
       vxball=-12;
       vyball=-12;
       xball+=vxball;
       yball+=vyball;
       shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock2="photos\\stock22.png";
    if(shooted2==false && xball>=xplay2-70 && xball<=xplay2-60 && yball>=yplay2+55 && yball<=yplay2+70 && ghost1==false){//shoot under foot
     vxball=-12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xplay2-70-cheatamountother && xball<=xplay2-50-cheatamountother &&  yball>=yplay2+30-cheatamountother && yball<yplay2+55 && ghost1==false){//shoot front foot
     vxball=-12;
     vyball=+8;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xplay2-50-cheatamountother && xball<=xplay2-20 &&  yball>=yplay2+30 && yball<yplay2+55  && ghost1==false){///shoot up of foot
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
     }
     shooted2=false;


          if(tripple2==true){
    if(xball>=xtripsecond1-80-cheatamountother && xball<=xtripsecond1-20 && yball>=ytripsecond1+25-cheatamountother && yball<=ytripsecond1+70  && ghost1==false){//shoot normal
       vxball=-12;
       vyball=-12;
       xball+=vxball;
       yball+=vyball;
       shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock2="photos\\stock22.png";
    if(shooted2==false && xball>=xtripsecond1-70 && xball<=xtripsecond1-60 && yball>=ytripsecond1+55 && yball<=ytripsecond1+70 && ghost1==false){///shoot under foot
     vxball=-12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xtripsecond1-70-cheatamountother && xball<=xtripsecond1-50-cheatamountother &&  yball>=ytripsecond1+30-cheatamountother && yball<ytripsecond1+55 && ghost1==false){///shoot front foot
     vxball=-12;
     vyball=+8;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xtripsecond1-50-cheatamountother && xball<=xtripsecond1-20 &&  yball>=ytripsecond1+30-cheatamountother && yball<ytripsecond1+55  && ghost1==false){///shoot up of foot
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
     }
     shooted2=false;


    if(xball>=xtripsecond2-80-cheatamountother && xball<=xtripsecond2-20 && yball>=ytripsecond2+25-cheatamountother && yball<=ytripsecond2+70 && ghost1==false ){//shoot normal
       vxball=-12;
       vyball=-12;
       xball+=vxball;
       yball+=vyball;
       shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
    stock2="photos\\stock22.png";
    if(shooted2==false && xball>=xtripsecond2-70 && xball<=xtripsecond2-60 && yball>=ytripsecond2+55 && yball<=ytripsecond2+70 && ghost1==false){//shoot under foot
     vxball=-12;
     vyball=+12;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xtripsecond2-70-cheatamountother && xball<=xtripsecond2-50-cheatamountother &&  yball>=ytripsecond2+30-cheatamountother && yball<ytripsecond2+55 && ghost1==false){//shoot front foot
     vxball=-12;
     vyball=+8;
     xball+=vxball;
     yball+=vyball;
     shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
    }
     if(shooted2==false && xball>=xtripsecond2-50-cheatamountother && xball<=xtripsecond2-20 &&  yball>=ytripsecond2+30-cheatamountother && yball<ytripsecond2+55  && ghost1==false){///shoot up of foot
        vxball=+12;
        vyball=-12;
        xball+=vxball;
        yball+=vyball;
        shooted2=true;
        Mix_Chunk *shooooot=Mix_LoadWAV("musics\\shoot.wav");
        Mix_PlayChannel(-1,shooooot,0);
     }
     shooted2=false;
          }
}
    if(keystate[SDL_SCANCODE_O]){/// theif power
        theif2=true;
        r=rand()%6;
    }
     if( (keystate[SDL_SCANCODE_M] || theif2==true) && powplay2>490 && dead2==false && ghost1==false  ){/// other powers
     powplay2=0;

    if(player2kind=="photos\\character21.png" || (theif2==true && r==0)){/// kick ball
    stock2="photos\\stock22.png";
    if(xball>=xplay2-80-cheatamountother && xball<=xplay2-20 && yball>=yplay2+25-cheatamountother && yball<=yplay2+70 && ghost1==false){//kick fire ball
        vxball=-25;
        kikbal2=true;
    }
    }
    if(player2kind=="photos\\character22.png" || (theif2==true && r==1)){///combat
        combat2=true;
        if(xplay2-xplay1<240){
            dead1=true;
            deadtime1=4;
        }
    }
    if( player2kind=="photos\\character23.png"  || (theif2==true && r==2)){/// invisible
        if( xplay2>xball && xplay2-xball<80+cheatamountother && yball>480-cheatamountother && yball<582 && ghost1==false){
            stock2="photos\\stock22.png";
            invisball=true;
            invistime=4;
            vxball=-10;
            vyball=-10;
        }
    }
    if(player2kind=="photos\\character24.png"  || (theif2==true && r==3)){///head fire ball
        if(xball<xplay2 && xplay2-xball<60+cheatamountother && yball<510 && yball>400-cheatamountother && ghost1==false){
            yball-=40+cheatamountother;
            yplay2=yball;
            xball=xplay2-10-cheatamountother;
        if( asin(200/ ((xball-50)*2*3.14) )<=(3.14/4)){
            vxball=-35;
            vyball=0;
        }
        else{
            vxball=-30;
            vyball=-10;
        }
        fire2=true;
        }
    }
    if( (player2kind=="photos\\character25.png" || (theif2==true && r==4) ) && xplay1<700){/// triple
        tripple2=true;
        triptime2=8;
    }
    if(player2kind=="photos\\character25.png"  && xplay1>700){
        powplay2=496;
    }
   if(player2kind=="photos\\character26.png" || (theif2==true && r==5)){/// ghost ball
        ghost2=true;
        ghosttime2=8;
    }
}

}
            }
theif1=false;
theif2=false;
if(xplay2-xplay1<181){///players couldn't pass each other
    xplay1=xplay2-180;
}
if(tripple1==true){
    if(xtripfirst2<0){
        xplay1-=xtripfirst2;
    }
}
if(tripple2==true){
    if(xtripsecond2>1120){
        xplay2-=(xtripsecond2-1120);
    }
}
if(goal1==endgoal || goal2==endgoal || boardtime==0){/// end rules are true
        Mix_Chunk *soot=Mix_LoadWAV("musics\\soot2.wav");
        Mix_PlayChannel(-1,soot,0);
    SDL_Delay(10);
    arr[firstgamercode].game++;
    arr[secondgamercode].game++;
    if(goal1>goal2){
        arr[firstgamercode].win++;
        arr[secondgamercode].lose++;
    }
    if(goal1<goal2){
        arr[firstgamercode].lose++;
        arr[secondgamercode].win++;
    }
    if(goal1==goal2){
        arr[firstgamercode].draw++;
        arr[secondgamercode].draw++;
    }
    ofstream fout1("tedad.txt", ios::out);
             fout1<<numberofgamers<<endl;
    	fout1.close();
    ofstream fout2("players.txt", ios::out);
             for(int i=0;i<numberofgamers;i++){
                fout2<<arr[i].name<<endl;
             }
    	fout2.close();
    ofstream fout3("jadval.txt", ios::out);
             for(int i=0;i<numberofgamers;i++){
                fout3<<arr[i].game<<endl;
                fout3<<arr[i].win<<endl;
                fout3<<arr[i].draw<<endl;
                fout3<<arr[i].lose<<endl;
             }
    	fout3.close();
    	bool stopper=true;
        bool scores=true;
    	while(stopper==true){
    texture(m_renderer,0,0,"photos\\stadiom.png",1200,700);
    texture(m_renderer,600,580,"photos\\ball.png",40,40);
    texture(m_renderer,xplay1,yplay1,player1kind,80,80);
    texture(m_renderer,xplay2,yplay2,player2kind,80,80);
    texture(m_renderer,xplay1+40,yplay1+60,stock1,100,50);
    texture(m_renderer,xplay2-60,yplay2+60,stock2,100,50);
    texture(m_renderer,0,440,"photos\\darvaz1.png",75,200);
    texture(m_renderer,1125,440,"photos\\darvaz2.png",75,200);
    string message="press any key to go home";
    textRGBA(m_renderer,10,80,gamername1,"font.ttf",32,0,0,0,255,0.0,0);
    textRGBA(m_renderer,1080,80,gamername2,"font.ttf",32,0,0,0,255,0.0,0);
    textRGBA(m_renderer,520,30,to_string(goal1),"font.ttf",48,0,0,0,255,0.0,0);
    textRGBA(m_renderer,670,30,to_string(goal2),"font.ttf",48,0,0,0,255,0.0,0);
    textRGBA(m_renderer,570,100,to_string(boardtime),"font.ttf",48,0,0,0,255,0.0,0);
    rect(m_renderer, 5,30,powplay1,50,255, 0, 0, 1);
    rect(m_renderer, 1195-powplay2,30,powplay2,50,0, 0, 255, 1);
    if(scores==true){/// show scores at end
        for(int k=0;k<=200;k+=4){
        texture(m_renderer,0,0,"photos\\stadiom.png",1200,700);
        texture(m_renderer,600,580,"photos\\ball.png",40,40);
        texture(m_renderer,xplay1,yplay1,player1kind,80,80);
        texture(m_renderer,xplay2,yplay2,player2kind,80,80);
        texture(m_renderer,xplay1+40,yplay1+60,stock1,100,50);
        texture(m_renderer,xplay2-60,yplay2+60,stock2,100,50);
        texture(m_renderer,0,420,"photos\\darvaz1.png",75,200);
        texture(m_renderer,1125,420,"photos\\darvaz2.png",75,200);
        string message="press any key to go home";
        textRGBA(m_renderer,10,80,gamername1,"font.ttf",32,0,0,0,255,0.0,0);
        textRGBA(m_renderer,1080,80,gamername2,"font.ttf",32,0,0,0,255,0.0,0);
        textRGBA(m_renderer,520,30,to_string(goal1),"font.ttf",48,0,0,0,255,0.0,0);
        textRGBA(m_renderer,670,30,to_string(goal2),"font.ttf",48,0,0,0,255,0.0,0);
        textRGBA(m_renderer,570,100,to_string(boardtime),"font.ttf",48,0,0,0,255,0.0,0);
        rect(m_renderer, 5,30,powplay1,50,255, 0, 0, 1);
        rect(m_renderer, 1195-powplay2,30,powplay2,50,0, 0, 255, 1);
        texture(m_renderer,200,k,"photos\\back ground 2.jfif",800,300);
        SDL_RenderPresent( m_renderer );
        SDL_RenderClear( m_renderer );

        }
        scores=false;
    }
    texture(m_renderer,200,200,"photos\\back ground 2.jfif",800,300);
    texture(m_renderer,220,200,"photos\\cardback.png",200,200);
    texture(m_renderer,800,200,"photos\\cardback.png",200,200);
    texture(m_renderer,310,240,player1kind,40,40);
    texture(m_renderer,895,240,player2kind,40,40);
    textRGBA(m_renderer,300,300,gamername1,"font.ttf",30,0,255,0,255,0.0,0);
    textRGBA(m_renderer,880,300,gamername2,"font.ttf",30,0,255,0,255,0.0,0);
    textRGBA(m_renderer,325,350,to_string(goal1),"font.ttf",30,255,0,0,255,0.0,0);
    textRGBA(m_renderer,905,350,to_string(goal2),"font.ttf",30,255,0,0,255,0.0,0);
    if(goal1>goal2){/// end game and go to start page
            textRGBA(m_renderer,300,400,"winner","font.ttf",32,255,0,0,255,0.0,0);
    }
    if(goal1<goal2){
            textRGBA(m_renderer,880,400,"winner","font.ttf",32,255,0,0,255,0.0,0);
    }
    if(goal1==goal2){
            textRGBA(m_renderer,590,200,"draw","font.ttf",32,0,0,0,255,0.0,0);
    }
        texture(m_renderer,560,320,"photos\\gohome.png",80,80);
        SDL_RenderPresent( m_renderer );
        SDL_RenderClear( m_renderer );
        if(SDL_PollEvent(e)){
           if( e->type==SDL_MOUSEBUTTONDOWN){
            backgroundmusic=temp;
            Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); //Load background sound
            Mix_PlayMusic(GameSound,-1);
                running=true;
            waiter=0;
           while(running==true){

        texture(m_renderer,0,0,"photos\\waiting.jpg",1200,700);
        texture(m_renderer,350,445,"photos\\toolbar.png",500,100);


        waiter++;


        if(waiter>10){
        texture(m_renderer,360,460,"photos\\ball.png",55,55);
        }
        if(waiter>20){
        texture(m_renderer,400,460,"photos\\ball.png",55,55);
        }
        if(waiter>30){
        texture(m_renderer,440,460,"photos\\ball.png",55,55);
        }
        if(waiter>40){
        texture(m_renderer,480,460,"photos\\ball.png",55,55);
        }
        if(waiter>50){
        texture(m_renderer,520,460,"photos\\ball.png",55,55);
        }
        if(waiter>60){
        texture(m_renderer,560,460,"photos\\ball.png",55,55);
        }
        if(waiter>70){
        texture(m_renderer,600,460,"photos\\ball.png",55,55);
        }
        if(waiter>80){
        texture(m_renderer,640,460,"photos\\ball.png",55,55);
        }
        if(waiter>90){
        texture(m_renderer,680,460,"photos\\ball.png",55,55);
        }
        if(waiter>100){
        texture(m_renderer,720,460,"photos\\ball.png",55,55);
        }
        if(waiter>110){
        texture(m_renderer,760,460,"photos\\ball.png",55,55);
        }
        if(waiter>120){
        texture(m_renderer,800,460,"photos\\ball.png",55,55);
        }
        if(waiter<40){
            SDL_Delay(20);
        }
        if(waiter>40 && waiter<80){
            SDL_Delay(40);
        }
        if(waiter>80 && waiter<100){
            SDL_Delay(150);
        }
        if(waiter>125){
            waiter=130;
            SDL_Delay(10);
            running=false;
            runner=false;
            stopper=false;
            stadium=0;
            homepage=1;

        }
        SDL_RenderPresent( m_renderer );
        SDL_RenderClear( m_renderer );
           }
           }
        }

    	}

}
while(stoppage==true){/// stop page
    texture(m_renderer,0,0,"photos\\stadiom.png",1200,700);
    texture(m_renderer,xball,yball,"photos\\ball.png",40,40);
    texture(m_renderer,xplay1,yplay1,player1kind,80,80);
    texture(m_renderer,xplay2,yplay2,player2kind,80,80);
    texture(m_renderer,xplay1+40,yplay1+60,stock1,100,50);
    texture(m_renderer,xplay2-60,yplay2+60,stock2,100,50);
    texture(m_renderer,0,420,"photos\\darvaz1.png",75,200);
    texture(m_renderer,1125,420,"photos\\darvaz2.png",75,200);
    texture(m_renderer,400,150,"photos\\stoppage.png",400,400);
    textRGBA(m_renderer,10,80,gamername1,"font.ttf",32,0,0,0,255,0.0,0);
    textRGBA(m_renderer,1080,80,gamername2,"font.ttf",32,0,0,0,255,0.0,0);
    textRGBA(m_renderer,520,30,to_string(goal1),"font.ttf",48,0,0,0,255,0.0,0);
    textRGBA(m_renderer,670,30,to_string(goal2),"font.ttf",48,0,0,0,255,0.0,0);
    textRGBA(m_renderer,570,100,to_string(boardtime),"font.ttf",48,0,0,0,255,0.0,0);
    rect(m_renderer, 5,30,powplay1,50,255, 0, 0, 1);
    rect(m_renderer, 1195-powplay2,30,powplay2,50,0, 0, 255, 1);
    now=SDL_GetTicks();
    if(now>previous+1000){
        previous=now;
    }

    if(SDL_PollEvent(e)){
        if(e->type==SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&as,&cd);
            if(e->button.button==SDL_BUTTON_LEFT){/// save game

                if(as>410 && as<580 && cd>160 && cd<340){
                    stoppage=false;
        Mix_Chunk *soot=Mix_LoadWAV("musics\\soot1.wav");
        Mix_PlayChannel(-1,soot,0);
                }
                if(as>620 && as<780 && cd>160 && cd<340){
                      ofstream fout("save.txt", ios::out);
fout<<gamername1<<endl;
fout<<gamername2<<endl;
fout<<player1kind<<endl;
fout<<player2kind<<endl;
fout<<backgroundmusic<<endl;
fout<<endgoal<<endl;
fout<<endtime<<endl;
fout<<hardness<<endl;
fout<<firstgamercode<<endl;
fout<<secondgamercode<<endl;
fout<<xball<<endl;
fout<<yball<<endl;
fout<<xplay1<<endl;
fout<<yplay1<<endl;
fout<<xplay2<<endl;
fout<<yplay2<<endl;
fout<<powplay1<<endl;
fout<<powplay2<<endl;
fout<<vxball<<endl;
fout<<vyball<<endl;
fout<<vyplay1<<endl;
fout<<vyplay2<<endl;
fout<<geranesh<<endl;
fout<<ayball<<endl;
fout<<axball<<endl;
fout<<goal1<<endl;
fout<<goal2<<endl;
fout<<stock1<<endl;
fout<<stock2<<endl;
fout<<shooted1<<endl;
fout<<shooted2<<endl;
fout<<boardtime<<endl;
fout<<kikbal1<<endl;
fout<<kikbal2<<endl;
fout<<deadtime1<<endl;
fout<<deadtime2<<endl;
fout<<dead1<<endl;
fout<<dead2<<endl;
fout<<birdnumber<<endl;
fout<<birdsymbol<<endl;
fout<<combat1<<endl;
fout<<combat2<<endl;
fout<<invisball<<endl;
fout<<invistime<<endl;
fout<<fire1<<endl;
fout<<fire2<<endl;
fout<<tripple1<<endl;
fout<<tripple2<<endl;
fout<<triptime1<<endl;
fout<<triptime2<<endl;
fout<<xtripfirst1<<endl;
fout<<xtripfirst2<<endl;
fout<<ytripfirst1<<endl;
fout<<ytripfirst2<<endl;
fout<<xtripsecond1<<endl;
fout<<xtripsecond2<<endl;
fout<<ytripsecond1<<endl;
fout<<ytripsecond2<<endl;
fout<<stadiumfan<<endl;
fout<<fannumber<<endl;
fout<<myball<<endl;
fout<<ballnumber<<endl;
fout<<ghost1<<endl;
fout<<ghost2<<endl;
fout<<ghosttime1<<endl;
fout<<ghosttime2<<endl;
fout<<theif1<<endl;
fout<<theif2<<endl;
fout<<r<<endl;
fout<<cheat<<endl;
fout<<cheattime<<endl;
fout<<cheatchance<<endl;
fout<<cheatamountball<<endl;
fout<<cheatamountother<<endl;
fout<<prize1<<endl;
fout<<prize2<<endl;
fout<<prize3<<endl;
    	                fout.close();
                }
                if(as>410 && as<580 && cd>360 && cd<540){/// go home page
                    stoppage=false;
                    runner=false;
                    stadium=0;
                    homepage=1;
            backgroundmusic=temp;
            Mix_Music *GameSound = Mix_LoadMUS(backgroundmusic.c_str()); ///Load background sound
            Mix_PlayMusic(GameSound,-1);

                }
                if(as>610 && as<780 && cd>360 && cd<540){/// exit program
                    stoppage=false;
                    runner=false;
                    stadium=0;
                    homepage=0;
                    endpage=1;

                }
            }
        }
    }
        SDL_RenderPresent( m_renderer );
        SDL_RenderClear( m_renderer );
}


SDL_Delay(16.66);

    }
}
}
