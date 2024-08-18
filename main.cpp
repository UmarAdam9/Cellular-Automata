#include <iostream>
#include<chrono>
#include<vector>
#include "MyRenderer.h"



using namespace std;

int screenwidth=200;
int screenheight=200;





const int gridwidth=200;
const int gridheight=200;
int grid[gridwidth*gridheight]={};

const int empty_id= 9;
const int sand_id = 1;
const int water_id=2;
const int earth_id=3;
const int lava_id = 4;
const int semi_lava=5;
const int steam_id=6;
const int acid_id=7;
const int half_earth=8;

//red , green , blue , yellow , brown
//lava, acid   ,water ,sand , land

struct Particle{

    int Posx;
    int Posy;
    int position;
    int forward_position;
    int forward_right_position;
    int forward_left_position;
    int backward_position;
    int backward_right_position;
    int backward_left_position;
    int left_position;
    int right_position;
    int id;
    int life;

    Particle(int x,int y,int i,int l=1){

    Posx = x;
    Posy = y;
    id = i;
    position= (Posy*gridwidth)+Posx;
    forward_position = ((Posy+1)*gridwidth)+Posx;
    forward_right_position = ((Posy+1)*gridwidth)+Posx+1;
    forward_left_position = ((Posy+1)*gridwidth)+Posx-1;
    left_position = ((Posy)*gridwidth)+Posx-1;
    right_position = ((Posy)*gridwidth)+Posx+1;
    life=l;

    }

    void UpdatePosition(int x,int y){

    Posx += x;
    Posy += y;
    position = (Posy*gridwidth)+Posx;
    forward_position = ((Posy+1)*gridwidth)+Posx;
    backward_position = ((Posy-1)*gridwidth)+Posx;
    forward_right_position = ((Posy+1)*gridwidth)+Posx+1;
    backward_right_position = ((Posy-1)*gridwidth)+Posx+1;
    forward_left_position  = ((Posy+1)*gridwidth)+Posx-1;
    backward_left_position  = ((Posy-1)*gridwidth)+Posx-1;
    left_position  = ((Posy)*gridwidth)+Posx-1;
    right_position = ((Posy)*gridwidth)+Posx+1;

    grid[position]=id;

    }

};



vector<Particle>vec_particles;


void updateParticle(Particle &p){

switch (p.id){



case sand_id:
        if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== empty_id)                           {grid[p.position]= empty_id; p.UpdatePosition(0,1);}
        else if(p.forward_right_position < (gridwidth*gridheight - 1) && p.forward_right_position >0 && grid[p.forward_right_position]== empty_id)    {grid[p.position]=empty_id; p.UpdatePosition(1,1);}
        else if(p.forward_left_position  < (gridwidth*gridheight - 1) && p.forward_left_position >0  && grid[p.forward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,1);}
        else{/**do nothing**/}


        break;

case water_id:
        if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== lava_id){
                p.id = steam_id; p.UpdatePosition(0,0);
                for(int i=0;i<vec_particles.size();i++){
                            if(vec_particles[i].position == p.forward_position)
                            {
                                vec_particles[i].id = semi_lava;
                                grid[vec_particles[i].position] = semi_lava;
                            }

                    }



            }

        else if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== empty_id)                         { grid[p.position]= empty_id; p.UpdatePosition(0,1);}
        else if(p.forward_right_position < (gridwidth*gridheight - 1) && p.forward_right_position >0 && grid[p.forward_right_position]== empty_id)  {grid[p.position]=empty_id; p.UpdatePosition(1,1);}
        else if(p.forward_left_position < (gridwidth*gridheight - 1) && p.forward_left_position >0 && grid[p.forward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,1);}
        else if(p.right_position < (gridwidth*gridheight - 1) && p.right_position >0 &&grid[p.right_position]== empty_id)                           {grid[p.position]=empty_id; p.UpdatePosition(1,0);}
        else if(p.left_position < (gridwidth*gridheight - 1) && p.left_position >0 && grid[p.left_position]== empty_id)                             {grid[p.position]=empty_id; p.UpdatePosition(-1,0);}

        else{/**do nothing**/}

     break;

case earth_id:
          p.UpdatePosition(0,0);

     break;

case lava_id:
        if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== water_id)  {
                    p.id = semi_lava; p.UpdatePosition(0,0);
                    for(int i=0;i<vec_particles.size();i++){
                            if(vec_particles[i].position == p.forward_position)
                            {
                                vec_particles[i].id = steam_id;
                                grid[vec_particles[i].position] = steam_id;
                            }

                    }
            }
        else if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== empty_id)                         { grid[p.position]= empty_id; p.UpdatePosition(0,1);}
        else if(p.forward_right_position < (gridwidth*gridheight - 1) && p.forward_right_position >0 && grid[p.forward_right_position]== empty_id)  {grid[p.position]=empty_id; p.UpdatePosition(1,1);}
        else if(p.forward_left_position < (gridwidth*gridheight - 1) && p.forward_left_position >0 && grid[p.forward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,1);}
        else if(p.right_position < (gridwidth*gridheight - 1) && p.right_position >0 &&grid[p.right_position]== empty_id)                           {grid[p.position]=empty_id; p.UpdatePosition(1,0);}
        else if(p.left_position < (gridwidth*gridheight - 1) && p.left_position >0 && grid[p.left_position]== empty_id)                             {grid[p.position]=empty_id; p.UpdatePosition(-1,0);}

        else{/**do nothing**/}

     break;


case steam_id:
//    p.UpdatePosition(0,0);
        if(p.backward_position < (gridwidth*gridheight - 1) && p.backward_position >0 && grid[p.backward_position]== empty_id)                         { grid[p.position]= empty_id; p.UpdatePosition(0,-1);}
        else if(p.backward_right_position < (gridwidth*gridheight - 1) && p.backward_right_position >0 && grid[p.backward_right_position]== empty_id)  {grid[p.position]=empty_id; p.UpdatePosition(1,-1);}
        else if(p.backward_left_position < (gridwidth*gridheight - 1) && p.backward_left_position >0 && grid[p.backward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,-1);}
        else if(p.right_position < (gridwidth*gridheight - 1) && p.right_position >0 &&grid[p.right_position]== empty_id)                              {grid[p.position]=empty_id; p.UpdatePosition(1,0);}
        else if(p.left_position < (gridwidth*gridheight - 1) && p.left_position >0 && grid[p.left_position]== empty_id)                                {grid[p.position]=empty_id; p.UpdatePosition(-1,0);}

        else{/**do nothing**/}
    break;

case semi_lava:
      if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== empty_id)                           {grid[p.position]= empty_id; p.UpdatePosition(0,1);}
        else if(p.forward_right_position < (gridwidth*gridheight - 1) && p.forward_right_position >0 && grid[p.forward_right_position]== empty_id)    {grid[p.position]=empty_id; p.UpdatePosition(1,1);}
        else if(p.forward_left_position  < (gridwidth*gridheight - 1) && p.forward_left_position >0  && grid[p.forward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,1);}
        else{/**do nothing**/}
    break;


case acid_id:


           if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== semi_lava){
                        for(int i=0;i<vec_particles.size();i++){
                                    if(vec_particles[i].position == p.forward_position)
                                    {

                                            vec_particles[i].id = empty_id;
                                            grid[vec_particles[i].position] = empty_id;


                                    }

                            }



                    }
            if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== earth_id){
                        for(int i=0;i<vec_particles.size();i++){
                                    if(vec_particles[i].position == p.forward_position)
                                    {
                                        vec_particles[i].life--;

                                        if(vec_particles[i].life==0)
                                        {
                                            vec_particles[i].id = empty_id;
                                            grid[vec_particles[i].position] = empty_id;
                                        }

                                    }

                            }



                    }
            if(p.right_position < (gridwidth*gridheight - 1) && p.right_position >0 && grid[p.right_position]== earth_id){
                        for(int i=0;i<vec_particles.size();i++){
                                    if(vec_particles[i].position == p.right_position)
                                    {
                                        vec_particles[i].life--;

                                        if(vec_particles[i].life==0)
                                        {
                                            vec_particles[i].id = empty_id;
                                            grid[vec_particles[i].position] = empty_id;
                                        }

                                    }

                            }



                    }
            if(p.left_position < (gridwidth*gridheight - 1) && p.left_position >0 && grid[p.left_position]== earth_id){
                        for(int i=0;i<vec_particles.size();i++){
                                    if(vec_particles[i].position == p.left_position)
                                    {
                                        vec_particles[i].life--;

                                        if(vec_particles[i].life==0)
                                        {
                                            vec_particles[i].id = empty_id;
                                            grid[vec_particles[i].position] = empty_id;
                                        }

                                    }

                            }



                    }



        else if(p.forward_position < (gridwidth*gridheight - 1) && p.forward_position >0 && grid[p.forward_position]== empty_id)                         { grid[p.position]= empty_id; p.UpdatePosition(0,1);}
        else if(p.forward_right_position < (gridwidth*gridheight - 1) && p.forward_right_position >0 && grid[p.forward_right_position]== empty_id)  {grid[p.position]=empty_id; p.UpdatePosition(1,1);}
        else if(p.forward_left_position < (gridwidth*gridheight - 1) && p.forward_left_position >0 && grid[p.forward_left_position]== empty_id)     {grid[p.position]=empty_id; p.UpdatePosition(-1,1);}
        else if(p.right_position < (gridwidth*gridheight - 1) && p.right_position >0 &&grid[p.right_position]== empty_id)                           {grid[p.position]=empty_id; p.UpdatePosition(1,0);}
        else if(p.left_position < (gridwidth*gridheight - 1) && p.left_position >0 && grid[p.left_position]== empty_id)                             {grid[p.position]=empty_id; p.UpdatePosition(-1,0);}


        else{/**do nothing**/}
    break;




}

}





void CreateWaterParticle(int x,int y){

Particle p(x,y,water_id);
vec_particles.push_back(p);
}
void CreateSandParticle(int x,int y){

Particle p(x,y,sand_id);
vec_particles.push_back(p);
}
void CreateEarthParticle(int x,int y){
Particle p(x,y,earth_id,30);
vec_particles.push_back(p);
Particle p1(x,y+1,earth_id);
vec_particles.push_back(p1);
Particle p2(x,y-1,earth_id);
vec_particles.push_back(p2);
Particle p3(x+1,y,earth_id);
vec_particles.push_back(p3);
Particle p4(x-1,y,earth_id);
vec_particles.push_back(p4);
Particle p5(x+1,y+1,earth_id);
vec_particles.push_back(p5);
Particle p6(x-1,y-1,earth_id);
vec_particles.push_back(p6);
Particle p7(x+1,y-1,earth_id);
vec_particles.push_back(p7);
Particle p8(x-1,y+1,earth_id);
vec_particles.push_back(p8);
}
void CreateLavaParticle(int x,int y){

Particle p(x,y,lava_id);
vec_particles.push_back(p);
}
void CreateAcidParticle(int x,int y){

Particle p(x,y,acid_id);
vec_particles.push_back(p);
}


void CreateEraserParticle(int x,int y){

    int pos1 = y*gridwidth+x;
    int pos2 = (y+1)*gridwidth+x;
    int pos3 = (y-1)*gridwidth+x;
    int pos4 = y*gridwidth+(x+1);
    int pos5 = y*gridwidth+(x-1);
    int pos6 = (y+1)*gridwidth+(x+1);
    int pos7 = (y+1)*gridwidth+(x-1);
    int pos8 = (y-1)*gridwidth+(x+1);
    int pos9 = (y-1)*gridwidth+(x-1);



    for(int i=0; i<vec_particles.size();i++)
    {
     if(vec_particles[i].position == pos1)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos1] = empty_id;}
     if(vec_particles[i].position == pos2)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos2] = empty_id;}
     if(vec_particles[i].position == pos3)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos3] = empty_id;}
     if(vec_particles[i].position == pos4)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos4] = empty_id;}
     if(vec_particles[i].position == pos5)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos5] = empty_id;}
     if(vec_particles[i].position == pos6)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos6] = empty_id;}
     if(vec_particles[i].position == pos7)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos7] = empty_id;}
     if(vec_particles[i].position == pos8)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos8] = empty_id;}
     if(vec_particles[i].position == pos9)
        {vec_particles.erase(vec_particles.begin()+i); grid[pos9] = empty_id;}



    }


}



void init_grid(){
     for(int i=0;i<gridwidth;i++){
            for(int j=0;j<gridheight;j++)
            {
                grid[j*gridwidth+i]=empty_id;
            }
        }

}


int main()
{
 MyRenderer renderer;
 renderer.CreateConsole(screenwidth,screenheight,2,2);


 int x=100;
 int y=0;

 init_grid();


  while(1)
  {

        renderer.Fill(0,0,screenwidth,screenheight,PIXEL_SOLID,FG_GREY);


         Sleep(0);


        if(GetAsyncKeyState('W')){y-=1;}
        if(GetAsyncKeyState('S')){y+=1;}
        if(GetAsyncKeyState('A')){x-=1;}
        if(GetAsyncKeyState('D')){x+=1;}

        if(GetAsyncKeyState('M')){CreateLavaParticle(x,y);}
        if(GetAsyncKeyState('N')){CreateEarthParticle(x,y);}
        if(GetAsyncKeyState('B')){CreateSandParticle(x,y);}
        if(GetAsyncKeyState('V')){CreateWaterParticle(x,y);}
        if(GetAsyncKeyState('C')){CreateEraserParticle(x,y);}
        if(GetAsyncKeyState('X')){CreateAcidParticle(x,y);}



        for(auto &i : vec_particles){ if(i.Posy <= gridheight-2 && i.Posx <= gridwidth-1 && i.Posx >= 0 && i.Posy >= 0){ updateParticle(i);} }

        for(int i=0;i<gridwidth;i++){
            for(int j=0;j<gridheight;j++)
            {
                if(grid[j*gridwidth+i]==empty_id){renderer.Draw(i,j,PIXEL_SOLID,FG_BLACK);}
                if(grid[j*gridwidth+i]==sand_id){renderer.Draw(i,j,PIXEL_SOLID,FG_DARK_YELLOW);}
                if(grid[j*gridwidth+i]==water_id){renderer.Draw(i,j,PIXEL_SOLID,FG_BLUE);}
                if(grid[j*gridwidth+i]==earth_id){renderer.Draw(i,j,PIXEL_SOLID,FG_YELLOW);}
                if(grid[j*gridwidth+i]==lava_id){renderer.Draw(i,j,PIXEL_SOLID,FG_DARK_RED);}
                if(grid[j*gridwidth+i]==semi_lava){renderer.Draw(i,j,PIXEL_SOLID,FG_GREY);}
                if(grid[j*gridwidth+i]==steam_id){renderer.Draw(i,j,PIXEL_HALF,FG_WHITE);}
                if(grid[j*gridwidth+i]==acid_id){renderer.Draw(i,j,PIXEL_SOLID,FG_DARK_GREEN);}
                if(grid[j*gridwidth+i]==half_earth){renderer.Draw(i,j,PIXEL_THREEQUARTERS,FG_YELLOW);}
            }
         }



        renderer.FillCircle(x,y,5);





        renderer.WriteToBuffer();
  }


    return 0;
}

