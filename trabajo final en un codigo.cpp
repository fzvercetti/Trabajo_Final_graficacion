//Librer?as
#include<iostream>
#include<GL/glut.h>
using namespace std;

/*INTEGRANTES
Felipe de Jes?s Zamora Baldazo
Jes?s Mart?n Hern?ndez Hern?ndez
Oscar Uriel Chav?z Estrada
*/

//voids instaciados
void display();
void setMaterial();
void init();
void addQuad();
void drawQuads();
void Car();
void drawGrid();
void keyboard(unsigned char key,int x, int y);

//Variables
int cx=0,cy=0,cz=0;
int cn;

void setMaterial ( GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, 
		   GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB, 
		   GLfloat specularR, GLfloat specularG, GLfloat specularB,
		   GLfloat shininess) 
 {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}		   

struct Quads{
	
  int x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
  float r,g,b;
  int state;
  int total;	
}; Quads Q[100];

void addQuad(){
	
	Q[0].state++; if(Q[0].state>4){ Q[0].state=1;}
	int st=Q[0].state;
	
	if(st==1){ Q[0].total++; cn =Q[0].total;}
	if(st==1                     ){Q[cn].x1=cx; Q[cn].y1=cy; Q[cn].z1=cz;}
	if(st==1||st==2              ){Q[cn].x2=cx; Q[cn].y2=cy; Q[cn].z2=cz;}
	if(st==1||st==2||st==3       ){Q[cn].x3=cx; Q[cn].y3=cy; Q[cn].z3=cz;}
	if(st==1||st==2||st==3||st==4){Q[cn].x4=cx; Q[cn].y4=cy; Q[cn].z4=cz;}	
};

void drawQuads(){
int i;
	for(i=1;i<Q[0].total+1;i++)
	{
	glBegin(GL_QUADS);
	glColor3f(Q[i].r,Q[i].g,Q[i].b);
	glVertex3f(Q[i].x1,Q[i].y1,Q[i].z1);
	glVertex3f(Q[i].x2,Q[i].y2,Q[i].z2);
	glVertex3f(Q[i].x3,Q[i].y3,Q[i].z3);
	glVertex3f(Q[i].x4,Q[i].y4,Q[i].z4);	
	glEnd();
	}
};

void drawGrid(){
	
int i;
	for(i=0;i<40;i++){
		
		glPushMatrix();
		if(i< 20){ glTranslatef(0,0,i);}
		if(i>=20){ glTranslatef(i-20,0,0); glRotatef(-90,0,1,0);}
	
		glBegin(GL_LINES);
		glColor3f(1,1,1); glLineWidth(1);
		glVertex3f(0,-0.1,0); glVertex3f(19,-0.1,0);
		glEnd();
		glPopMatrix();
	}
}

void Car(){
// car //carrito del free fire
    setMaterial(1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,50);
    glTranslatef(cx,cy,cz);
    glPushMatrix();
    glPushMatrix();                   // body //cuerpo
    glScalef(2,.5,1);
    glutSolidCube(.5);
    glPopMatrix();
    glTranslatef(0,0,.25);
    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel //rueda
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel //rueda
    glPopMatrix();
    glTranslatef(0,0,-.5);
    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel //rueda
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel //rueda
    glPopMatrix();
    glPopMatrix();
	}
	
void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13,0,-45);
	glRotatef(40,1,1,0);

	drawGrid();
	drawQuads();
	Car();
	glutSwapBuffers();
}

void init(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2,0.2,0.2,1);
}

void keyboard(unsigned char key,int x, int y){
	
	if(key=='w'){cz-=1;}if(key=='s'){cz+=1;}   //forward //back //Adelante //atr?s
	if(key=='a'){cx-=1;}if(key=='d'){cx+=1;}   //left //back   //izquierda//Atr?s
	if(key=='q'){cy-=1;}if(key=='z'){cy-=1;}   //up   //down  //Arriba   //Abajo
	
	if(key==32){addQuad();}					//Spacebar //barra espaciadora
	
	if(key=='r'){ Q[cn].r=1; Q[cn].g=0; Q[cn].b=0; } 
	if(key=='g'){ Q[cn].r=163; Q[cn].g=73; Q[cn].b=164; }
	if(key=='b'){ Q[cn].r=255; Q[cn].g=255; Q[cn].b=255; }
	if(key=='y'){ Q[cn].r=1; Q[cn].g=0; Q[cn].b=0; }
		
	glutPostRedisplay();
}	

int main(int argc, char **argv){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutCreateWindow("El trabajo final en un c?digo");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	
	// luces
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightpos[] = { 0.0, 15.0, 15.0 };
    GLfloat lightcolor[] = { 0.5, 0.5, 0.5 };
    GLfloat ambcolor[] = { 0.2, 0.2, 0.0 };

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightcolor);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);

	return 0;
}
