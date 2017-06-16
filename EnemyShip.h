#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
#include "EnemyProyectile.h"

class EnemyShip
{
public:
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat imagen;
	bool state;
	int respawn;
	int score;
	EnemyProyectile shot;

	int timer;
	int timebase;
	int deltatime;
	int anim;

	GLfloat mov;

	EnemyShip(GLfloat r,int sc)
	{
		imagen = TextureManager::Inst()->LoadTexture("image/navenemiga.png", GL_BGRA_EXT, GL_RGBA);

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;

		mov=0.01;

		radio=r;
		coordx=rand()%20-10;
		coordy=rand()%5+5;
		coordz=rand()%20-10;
		state=true;
		score=sc;

		shot.large=0.1f;
		shot.velocity=0.1f;
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
		if(!state)
		{
			timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
			deltatime = timer -timebase;// delta time
			timebase = timer;
			anim += deltatime;

			if (anim / 1000.0 > 0.15)
			{
				shoot();
				anim=0;
			}
			return;
		}
		glBindTexture(GL_TEXTURE_2D, imagen);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//dl
		glTexCoord2f(0.0,1.0);
		glVertex3d(Left(), Up(), 0);//ul
		glTexCoord2f(1.0,1.0);
		glVertex3d(Right(), Up(), 0);//ur
		glTexCoord2f(1.0,0.0);
		glVertex3d(Right(), Down(), 0);//dr
		glEnd();

		coordx+=mov;
		if(coordx >= 16.0f && coordx <= -16.0f)
			mov=mov*(-1.0f);

		shot.draw();
	}

	void shoot()
	{
		shot.state=true;
		shot.coordx=coordx;
		shot.coordy=coordy-radio-shot.large;
	}
	
};

#endif