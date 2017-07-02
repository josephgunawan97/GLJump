/*
GLJUMP
JOSEPH
LIVIA A.
*/
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <bits/stdc++.h>
#include <string>
/**************GLOBALS***************************************************/
GLfloat ball_x=0.5f,ball_y=0.0f;
float speed=0.005f;
float gravity = -0.00002f;
float rot=90;
float velocityX = 0.01, velocityY=0.0002f;     // Velocity of the character
int _switch=5;
float step_y=0,increment;
float step_x;
char buffer[12]={'\0'};
 const int font = (int)GLUT_BITMAP_8_BY_13;
float max=0;
bool gameover=false;
bool start = false;
/***********************************************************************/

void drawPlayer()
{

    glColor3f(1,1,0);
         //HEAD
          // glutWireSphere(1,16,16);
           glPushMatrix();
           glTranslatef(0,0.5,0);
           glutSolidSphere(1,16,16);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,-1,0);
          glScalef(1,1.5,1);
           glutSolidCube(1);
            glPopMatrix();
           //glRectf(0.5,0,-0.5,-2);//BODY


           //EYE
           glPushMatrix();
            glDisable (GL_LIGHTING);
            glColor3f(0,0,0);
            glTranslatef(0,0.4,0.9);
            glPointSize(4);
            glBegin(GL_POINTS);
            glVertex2f( 0.5 ,0 );
            glVertex2f( -0.5 ,0 );
            glEnd();
            glEnable (GL_LIGHTING);
            glPopMatrix();

              glColor3f(1,1,0);
           //LEG
           glPushMatrix();
            glTranslatef(-0.3,-2,0);
          glScalef(0.2,2,0.9);
           glutSolidCube(1);

            glTranslatef(3.2,0,0);
           glutSolidCube(1);
         //  glRectf(0.45,-2,0.3,-3);
         //  glRectf(-0.45,-2,-0.3,-3);
           glPopMatrix();

            //HAND
            glPushMatrix();


       // glTranslatef(-1.2,-0.5,0);
           glRotatef(rot,0,0,1);
            glTranslatef(-0.8,-0.5,0);
            glScalef(1.1,0.3,0.9);

           glutSolidCube(1);
         //  glRectf(0.15,0,0.3,-1.5);

           glPopMatrix();
           glPushMatrix();

           // glTranslatef(-0.5,3,0);
           glRotatef(-rot,0,0,1);
            glTranslatef(0.8,-0.5,0);
            glScalef(1.1,0.3,0.9);
           // glTranslatef(0.5,-3,0);

           glutSolidCube(1);
          // glRectf(-0.15,0,-0.3,-1.5);
          glPopMatrix();

}
void Jump()
{


    //velocityY=0.01f;
   // velocityY += gravity;

    if (_switch==0)
    ball_x += velocityX;
    else
        ;
    if(ball_x < -20.0f || ball_x > 20.0f)
        velocityX *= -1;

       // velocityY+=0.001f;
        velocityY+= gravity;
        ball_y+= velocityY;
         if(ball_y>=-6.0f&& ball_y <= -5.0f && ball_x<2.0f &&ball_x>-2.0f) {


            velocityY=0.020f;
            ball_y+= velocityY;
         }
         if(ball_y<ball_y+velocityY)
            rot=90;
        else if(ball_y>=ball_y+velocityY)
            rot=-30;

        glutPostRedisplay();

}

void renderBitmapString(float x, float y, void *font, const char *string)
{
    const char *c;
    glRasterPos3f(x, y, 0);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void display1()
{

    if(max<ball_y)
    {
        max=ball_y*10;

    }
    sprintf(buffer, "%.2f", max); //%d is for integers


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix ();

    GLfloat light_position1[] = { 0, 10.00, 30, 0.5};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);


   glTranslated (0.0, 0.0, 1.5);
   glDisable (GL_LIGHTING);
   glEnable (GL_LIGHTING);
   glPopMatrix ();

  glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

            glTranslatef(ball_x,ball_y,0);
            drawPlayer();

    glPopMatrix();
    glPushMatrix();




            glDisable (GL_LIGHTING);
            glPushMatrix();
/*
     glBegin(GL_LINES); // COORDINATE LINES
		glColor3f( 1.0f, 1.0f, 1.0f);
		int max_lin = 20.0f;
		// horizontal
		for (int i=-20;i<=20;i++)
		{glVertex3f(20, i, -5.0f);
		glVertex3f(-20, i, -5.0f);
		}
		//vertical
		for(int i=-20;i<=20;i++)
        {
		glVertex3f(i, 20,-5.0f);
		glVertex3f(i,-20, -5.0f);
        }
    glEnd();
*/
   glTranslatef(0,-8,0);
            glScalef(3,1,0);
            glutSolidCube(1);
    glPopMatrix();

    glColor3f(0,0,0);
    renderBitmapString(-14,9, (void *)font, "Score :");
    renderBitmapString(-14,8, (void *)font, "Press F1 to Start Game");
    renderBitmapString(-11, 9, (void *)font, buffer);
    //output(-14,8,ss.str());
   // output(0,0,ball_y.);
    glPopMatrix();

    if(start==true)
          Jump();

    if(ball_y <-8.0f)
        gameover=true;

    if(gameover)
    {
        glPushMatrix();
        glScalef(2,2,0);
        renderBitmapString(-1,0, (void *)font, "GAME OVER");
        glPopMatrix();
    }
    glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, GLfloat(w)/GLfloat(h), 1.0, 100.0);
}

void init()
{

  glShadeModel(GL_SMOOTH);

    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);	// White Background
    glClearDepth(1.0f);	// Depth Buffer Setup

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  gluLookAt(0,0,25.0, 0.0, 0.0, 0.0, 0,20, 0);

}

void Move(int key, int, int)
{
 if(key==GLUT_KEY_LEFT)
 {

     _switch=0;
    velocityX=-0.01;

 }
 if(key==GLUT_KEY_RIGHT)
 {
     _switch=0;
    velocityX = 0.01;



 }
 else if (key==GLUT_KEY_F1)
 {
     start=true;
 }
 glutPostRedisplay();
}


void Stop(int key, int, int)
{

 if(key==GLUT_KEY_LEFT)
 {

     _switch=1;
    velocityX=0;

 }
 else if(key==GLUT_KEY_RIGHT)
 {

     _switch=1;
    velocityX =0;



 }
 glutPostRedisplay();
}

int main(int argc, char** argv)
 {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(600, 400);
  glutCreateWindow("GLJUMP");


  glutReshapeFunc(reshape);
  glutSpecialFunc(Move);
  glutSpecialUpFunc(Stop);
   glutDisplayFunc(display1);
  init();
  glutMainLoop();
}
