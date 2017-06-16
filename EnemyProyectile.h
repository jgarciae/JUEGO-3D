#ifndef ENEMYPROYECTILE_H
#define ENEMYPROYECTILE_H

#include <math.h>
#include "Enemy.h"

class EnemyProyectile
{
public:
	GLfloat large;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat velocity;
	bool state;
	GLfloat sprite;

	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	EnemyProyectile()
	{
		sprite = TextureManager::Inst()->LoadTexture("image/death_shot.png", GL_BGRA_EXT, GL_RGBA);
		state=false;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
	}


	GLfloat Right(){return coordx+large;}
	GLfloat Left(){return coordx-large;}
	GLfloat Up(){return coordy+large*4;}
	GLfloat Down(){return coordy-large*4;}

	void draw()
	{
		if(!state)
			return;
		
		glBindTexture(GL_TEXTURE_2D, sprite);
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

		if(coordy<=-11.0)
			state=false;
		coordy-=velocity;
	}

	/*bool collision(Ship *sh)
	{
		if( sqrt( pow(coordx - sh->coordx, 2) + pow(coordy - sh->coordy, 2) ) <= (large + sh->radio) && sh->state && state)
		{
			sh->state=false;
			state=false;
			return true;
		}
		return false;
	}*/

	
};

#endif