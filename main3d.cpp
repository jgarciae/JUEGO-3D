#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>

//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alut.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
//#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
#include "Bonus.h"
#include "EnemyShip.h"
//#include "Rock.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

GLfloat texture;

Ship *nave;
Enemy **enemigo;
Bonus **bono;

int num_enemigos=10;
int num_bonos=5;

int timer = 0;

//variables para el gizmo
float delta_x = 0.0; 
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)

const GLfloat light_ambient[]={0.0f,0.0f,0.0f,1.0f};
const GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat light_pos[]={2.0f,5.0f,5.0f,0.0f};

const GLfloat light_ambient2[]={0.1f,0.1f,0.1f,1.0f};
const GLfloat light_diffuse2[]={0.7f,0.0f,0.0f,1.0f};
const GLfloat light_specular2[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat light_pos2[]={2.0f,5.0f,5.0f,0.0f};

const GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
const GLfloat mat_diffuse[]={0.8f,0.8f,0.8f,1.0f};
const GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat high_shininess[]={100.0f};

void print()
{
	cout<<"var_x: "<<var_x<<endl;
	cout<<"var_z: "<<var_z<<endl;
	cout<<"delta_x: "<<delta_x<<endl;
	cout<<"delta_y: "<<delta_y<<endl;
	cout<<endl;
}

/*string life="LIFE: ";
void draw_life()
{
	glRasterPos2i(-15, -12);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < life.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)life[i]);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);

	for (int i = 0; i < nave->lives; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, sprites);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.666f);
		glVertex3d(-13.0f+i, -12.0f, 0);//dl
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(-13.0f+i, -11.0f, 0);//ul
		glTexCoord2f(0.2f,1.0f);
		glVertex3d(-12.0f+i, -11.0f, 0);//ur
		glTexCoord2f(0.2f,0.666f);
		glVertex3d(-12.0f+i, -12.0f, 0);//dr
		glEnd();
	}
}*/

string score="SCORE: ";
void draw_score()
{
	stringstream ss;
	ss<<nave->total_score;
	glRasterPos2i(-7, -12);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < score.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)score[i]);

	for (int i = 0; i < ss.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)ss.str()[i]);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}

string tm="TIME: ";
void draw_time()
{
	int t=timer/1000;

	stringstream minute;
	minute<<t/60;

	stringstream second;
	second<<t%60;

	glRasterPos2i(0, -18);
	//glColor3f( 0.0f, 0.0f, 1.0f);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < score.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)tm[i]);

	for (int i = 0; i < minute.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)minute.str()[i]);

	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)':');

	if(t%60<10)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)'0');

	for (int i = 0; i < second.str().size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)second.str()[i]);	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}


GLvoid initGL()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	//glEnable(GL_AUTO_NORMAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}


void Gizmo3D(){


	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	return;

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timer = glutGet(GLUT_ELAPSED_TIME); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);


	/*glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);*/

	glTranslatef(0.0, 0.0, -30.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(-75.0, 1.0, 0.0, 0.0);


	/*glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, texture);
	glutSolidCube(100);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);*/

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0);//coordenadas de textura
	glVertex3d(-50.0f, 50.0f, -60.0f);//dl
	glTexCoord2f(0.0,1.0);
	glVertex3d(-50.0f, 50.0f, 50.0f);//ul
	glTexCoord2f(1.0,1.0);
	glVertex3d(50.0f, 50.0f, 50.0f);//ur
	glTexCoord2f(1.0,0.0);
	glVertex3d(50.0f, 50.0f, -60.0f);//dr
    glEnd();



	nave->draw();


	
	/*for (int i = 0; i < num_enemigos; ++i)
	{
		enemigo[i]->draw();

		if(nave->shot.collision(enemigo[i]))
		{
			enemigo[i]->destroy();
			//cout<<"Enemigo "<<i<<" destruido"<<endl;
			nave->win(enemigo[i]->score);
			//cout<<"Puntaje: "<<nave->total_score<<endl;
		}

		//cout<<"nave->collision(enemigo[i]): "<<nave->collision(enemigo[i])<<endl;
		if(nave->collision(enemigo[i]))
		{
			nave->destroy();
			//cout<<"should be destroyed"<<endl;
		}
	}*/
	for (int i = 0; i < num_enemigos; ++i)
	{
		enemigo[i]->draw();

		if(nave->shots->collision(enemigo[i]))
		{
			enemigo[i]->destroy();
			cout<<"Enemigo "<<i<<" destruido"<<endl;
			nave->win(enemigo[i]->score);
			cout<<"Puntaje: "<<nave->total_score<<endl;
		}

		//cout<<"nave->collision(enemigo[i]): "<<nave->collision(enemigo[i])<<endl;
		if(nave->collision(enemigo[i]))
		{
			nave->destroy();
			//cout<<"should be destroyed"<<endl;
		}
	}

	
	
	for (int i = 0; i < num_bonos; ++i)
	{
		bono[i]->draw();

		if(nave->bonus_collision(bono[i]))
		{
			cout<<"Bono "<<i<<" cogido"<<endl;
			nave->win(bono[i]->score);
			cout<<"Puntaje: "<<nave->total_score<<endl;
		}
	}

	//draw_life();
	draw_score();
	draw_time();

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}



GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case ECHAP:
		exit(0);
		break;

	case 'a':
		nave->shoot();
		cout<<"Disparo"<<endl;
		break;
	case 'd':
		if(!nave -> explode)
			break;
		for (int i = 0; i < num_enemigos; ++i)
		{
			if(enemigo[i]->destroy())
				nave->win(enemigo[i]->score);
		}
		nave -> explode=false;
		cout<<"Explosion"<<endl;
		cout<<"Puntaje: "<<nave->total_score<<endl;
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}

}

//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
/*GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}*/

GLvoid callback_special(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_RIGHT: //d
		if(nave->Right()<15){
			nave->go_right();
			nave->rotate_right();
		}
		//cout<<"mueve derecha"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_LEFT: //f
		if(nave->Left()>-15){
			nave->go_left();
			nave->rotate_left();
		}
		//cout<<"mueve izquiera"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_UP: //e
		if(nave->Up()<15){
			nave->go_up();
			//nave->rotate_up();
		}
		//cout<<"mueve arriba"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_DOWN: //g
		if(nave->Down()>-15){
			nave->go_down();
			//nave->rotate_down();
		}
		//cout<<"mueve abajo"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	default:
		break;
	}

}

/*void callback_special_up(int key, int x, int y) 
{
	switch (key) 
	{
		case GLUT_KEY_RIGHT:
			break;

		case GLUT_KEY_LEFT:
			break;

		case GLUT_KEY_UP:
			break;

		case GLUT_KEY_DOWN:
			break;
	}
}*/


///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}

	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
		print();
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	
	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Milky Way");


	initGL();

	texture = TextureManager::Inst()->LoadTexture("image/space2.jpg", GL_BGR_EXT, GL_RGB);

	nave=new Ship(2.0f,0.0f,-5.0f,-10.0f,3);

	enemigo=new Enemy*[num_enemigos];
	for (int i = 0; i < num_enemigos; ++i)
		enemigo[i]=new Enemy(2.0f,50);

	bono=new Bonus*[num_bonos];
	for (int i = 0; i < num_bonos; ++i)
		bono[i]=new Bonus(1.0f,25,rand()%2);

	init_scene();

	
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	
	
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events
	
	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}




