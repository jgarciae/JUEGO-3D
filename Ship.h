#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"
#include "Bonus.h"
#include <iostream>
#include <unistd.h>
#include "Particle.h"


using namespace std;

class Ship
{
public:
	int lives;
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat cub;
	GLfloat cubd;
	GLfloat cubb;
	bool state;
	GLfloat sprite;
	int total_score;
	//Proyectile shot;
	Proyectiles *shots;

	bool explode;

	bool upgrade_shot;

	/*Proyectile *shot;
	int numshots;
	int count;*/

	GLfloat rotx;
	GLfloat roty;

	int iter;
	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Ship();

	Ship(GLfloat r, GLfloat xx, GLfloat yy,GLfloat zz, int lv)
	{
		//sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_BGRA_EXT, GL_RGBA);
		sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_RGB, GL_RGB);
		lives=lv;
		radio=r;
		coordx=xx;
		coordy=yy;
		coordz=zz;
		total_score=0;
		state=true;
		explode=false;

		//shot.large=0.25f;
		//shot.velocity=0.5f;
		shots=new Proyectiles(5);
		shots->large=0.25f;
		shots->velocity=0.5f;

		iter=0;
		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;

		rotx=0.0f;
		roty=0.0f;
		cub = TextureManager::Inst()->LoadTexture("image/cubiertanave.png", GL_BGRA_EXT, GL_RGB);
		cubd = TextureManager::Inst()->LoadTexture("image/cubiertanaveabajo.png", GL_BGRA_EXT, GL_RGB);
		cubb = TextureManager::Inst()->LoadTexture("image/cubiertaatras.png", GL_BGRA_EXT, GL_RGB);
		/*numshots=ns;
		shot=new Proyectile[ns];
		for (int i = 0; i < count; ++i)
		{
			shot[i].large=1.0f;
			shot[i].velocity=0.5f;
		}
		count=0;*/

		x = 0.25;
		y = 0.666;

		upgrade_shot=true;
	}

	/*void go_right(){coordx++;}
	void go_left(){coordx--;}
	void go_up(){coordy++;}
	void go_down(){coordy--;}*/

	void go_right(){coordx+=0.5;}
	void go_left(){coordx-=0.5;}
	void go_up(){coordz+=0.5;}
	void go_down(){coordz-=0.5;}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void rotate_right()
	{
		if(roty<=45.0f)
			roty++;
	}
	void rotate_left()
	{
		if(roty>=-45.0f)
			roty--;
	}
	void rotate_up()
	{
		if(rotx<=45.0f)
			rotx++;
	}
	void rotate_down()
	{
		if(rotx>=-45.0f)
			rotx-=2.0f;
	}

	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
	void normal(GLfloat ax,GLfloat ay, GLfloat az, GLfloat bx,GLfloat by, GLfloat bz)
	{
		nx=(ax*bz)-(az*by);
		ny=(az*bx)-(ax*bz);
		nz=(ax*by)-(ay*bx);
		GLfloat mod=(GLfloat)sqrt((nx*nx)+(ny*ny)+(nz*nz));
		nx/=mod;
		ny/=mod;
		nz/=mod;
	}

	void draw()
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if(!state)
			return;
//<<<<<<< HEAD
		
		//glTranslatef(5.0, 0.0, 0.0);

		glBindTexture(GL_TEXTURE_2D, sprite);
//=======
		glPushMatrix();
		glTranslatef(coordx,coordy,coordz)	;
//>>>>>>> 75d948e363a7a39801e141450e036656123d722f
		/*glBegin(GL_QUADS);
		//vértices en 3d
		glColor3f(1,0,0);//rojo
		glVertex3d(-2,0,-2);//4
		glColor3f(1,1,0);//amarillo
		glVertex3d(-2,0,2);//3
		glColor3f(0,0,1);//azul
		glVertex3d(2,0,2);//2
		glColor3f(0,1,0);//verde
		glVertex3d(2,0,-2);//1
		glEnd();
			//------------------caras de la pirámide
			//para las caras triangulares
			//se usará GL_TRIANGLES
			//--------Cara 4  amarillo con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,2,0);
			glColor3f(1,1,0);
			glVertex3d(-2,0,-2);//1
			glVertex3d(2,0,-2);//4
			glEnd();

			//--------Cara 1 rojo con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(1,0,0);//rojo
			glVertex3d(4,0,-4);
			glVertex3d(4,0,4);
			glEnd();
			//--------Cara 3 verde con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(0,1,0);//verde
			glVertex3d(-4,0,4);
			glVertex3d(-4,0,-4);
			glEnd();
			//-------Cara 2 azul con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(0,0,1);//azul
			glVertex3d(4,0,4);
			glVertex3d(-4,0,4);
			glEnd();*/


		//glRotatef(45.0, 1.0, 0.0, 0.0);
		glRotatef(rotx, 1.0, 0.0, 0.0);
		glRotatef(roty, 0.0, 1.0, 0.0);

		//normal(2*radio, radio, radio, )
		glBindTexture(GL_TEXTURE_2D, cubb);
		glBegin(GL_QUADS);
		normal(-2*radio,-1*radio,radio, 0,0,2*radio);
		glNormal3f(nx,ny,nz);
		glTexCoord2f(0.5,0.0);
		glVertex3d(0*radio,-1*radio,-1*radio);
		glTexCoord2f(0.0,0.5);
		glVertex3d(-2*radio,-2*radio,0*radio);
		normal(2*radio,radio,radio, 0,0,0);
		glNormal3f(nx,ny,nz);
		glTexCoord2f(0.5,1.0);
		glVertex3d(0*radio,-1*radio,1*radio);
		glTexCoord2f(1.0,0.5);
		glVertex3d(2*radio,-2*radio,0*radio);
		glEnd();

			normal(2*radio,4*radio,0,  2*radio,radio,radio);
			glBindTexture(GL_TEXTURE_2D, cub);
			glBegin(GL_TRIANGLES);
			//glColor3f(1,1,0); //amarillo
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(-2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,1*radio);
			glEnd();

			normal(-2*radio,4*radio,0, -2*radio,radio,radio);
			glBindTexture(GL_TEXTURE_2D, cub);
			glBegin(GL_TRIANGLES);
			//glColor3f(1,0,0);//rojo
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,1*radio);
			glEnd();


			normal(-2*radio,4*radio,0, -2*radio,radio,-1*radio);
			glBindTexture(GL_TEXTURE_2D, cubd);
			glBegin(GL_TRIANGLES);
			//glColor3f(0,1,0);//verde
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,-1*radio);
			glEnd();

			normal(2*radio,4*radio,0, 2*radio,radio,-1*radio);
			glBindTexture(GL_TEXTURE_2D, cubd);
			glBegin(GL_TRIANGLES);
			//glColor3f(0,0,1);//azul
			glNormal3f(nx,ny,nz);
			glTexCoord2f(0.0,0.0);
			glVertex3d(-2*radio,-2*radio,0*radio);
			glTexCoord2f(1.0,1.0);
			glVertex3d(0*radio,2*radio,0*radio);
			glTexCoord2f(1.0,0.25);
			glVertex3d(0*radio,-1*radio,-1*radio);
			glEnd();


		glPopMatrix();
		glColor3f(1,1,1);

		if (anim / 1000.0 > 0.15)
		{
			iter=(iter+1)%5;
			anim = 0;
		}
		shots->draw();

	}

	

	void win(int sc)
	{
		total_score+=sc;
	}

	/*void shoot()
	{
		shot.state=true;
		shot.coordx=coordx;
		shot.coordy=coordy+radio+shot.large;
		shot.coordz=coordz;
		//shot.coordz=coordz;
	}*/
	void shoot()
	{
		shots->initProyectile(coordx, coordy+radio+shots->large, coordz);
	}

	/*bool ifShot()
	{
		return shot.state;
	}*/

	bool destroy()
	{
		if (state)
		{
			state=false;
			lives--;
			return true;
		}
		return false;
	}

	bool bonus_collision(Bonus *b)
	{
		if( sqrt( pow(coordx - b->coordx, 2) + pow(coordy - b->coordy, 2) ) <= (radio + b->radio) && b->state && state)
		{
			b->state=false;
			if(b->type==0)
				explode=true;
			if(b->type==1)
				shots->upgrade();
			return true;
		}
		return false;
	}

	/*void shoot()
	{
		shot[count].state=true;
		shot[count].coordx=coordx;
		shot[count].coordy=coordy+radio+shot[count].large;
		count=(count+1)%numshots;
	}*/
	bool collision(Enemy *e)
	{
		/*for (int i = 0; i < numshots; ++i)
		{
			if (shot[i].collision(e))
				return true;
		}
		return false;*/

		
		/*cout<<"distancia: "<<sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) )<<endl;*/
		/*if( sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) ) <= (e->radio && (e->state && state)) )
		{
			cout<<"distancia: "<<sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) )<<endl;		
				
			e->state=false;
			sleep(1);
			if(lives==0){
				state=false;
			}	
				
			//explosion();
			lives--;
			return true;
		}
		return false;*/


		if(sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) +  pow(coordz - e->coordz, 2)) 
			<= e->radio+radio && e->state && state )
		{				
			e->state=false;
			sleep(1);
			if(lives==0){
				state=false;
			}	
				
			//explosion();
			lives--;
			return true;
		}
		return false;
	}

	//~Ship();
	
};

#endif
