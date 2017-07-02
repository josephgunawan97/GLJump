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
#include <bits/stdc++.h>
#include <GL/freeglut.h>
using namespace std;
/**************GLOBALS***************************************************/
GLfloat ball_x=0.5f, ball_y=0.0f;
float color = 0.1f, countercolor=0.03f;
float gravity = -0.000071f, fall_y=-0.00006f; //falling mechanism
float rot=90;
float velocityX = 0.0020, velocityY=0.008f;     // Velocity of the character
vector<float>step_y(7);
vector<float>step_x(7);// obstacle Y,X
char buffer[12]= {'\0'}; //store string etc
const int font = (int)GLUT_BITMAP_9_BY_15;
const int font2= (int)GLUT_BITMAP_TIMES_ROMAN_24;
float font_mx=-0.003f;
float maks=0; // for scoring method
bool start = false;
bool gameover=false;
bool moveX = false; //switch for keyboard input (left and right movement)
float Eye, camera=-20; // camera
float velocity_enemy=0.0035f, enemy_rot=0;
vector<float>enemy_y(3);
vector<float>enemy_x(3);
float x_anim=2.5;
float y_anim=-8;
float y_grav =0.005f;
float speed_anim=-0.00095f;
float counter=0;
/***********************************************************************/
float Random(float min, float max)
{
    return ((max-min)*((float)rand()/(float)RAND_MAX)) + min;
}

void drawEnemy()
{
    glRotated(enemy_rot,0,0,1);
    glScalef(0.65,0.65,0);
    glColor3f(0,1,0.5);
    glPushMatrix();
    glTranslatef(0,0,0);
    glutSolidSphere(0.5,16,16);
    glPopMatrix();

    glPushMatrix();
    glRotatef(45,1,1,0);
    glTranslatef(0,0,0);
    glutSolidCone(0.5,2,2,100);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-45,1,1,0);
    glTranslatef(0,0,0);
    glutSolidCone(0.5,2,2,100);
    glPopMatrix();
    glPushMatrix();
    glRotatef(45,-1,1,0);
    glTranslatef(0,0,0);
    glutSolidCone(0.5,2,2,100);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-45,-1,1,0);
    glTranslatef(0,0,0);
    glutSolidCone(0.5,2,2,100);
    glPopMatrix();
    enemy_rot+=1;
}

void drawPlayer()
{
    glColor3f(1,1,0);
    //HEAD
    glPushMatrix();
    glTranslatef(0,0.5,0);
    glutSolidSphere(1,16,16);
    glPopMatrix();
    //BODY
    glPushMatrix();
    glTranslatef(0,-1,0);
    glScalef(1,1.5,1);
    glutSolidCube(1);
    glPopMatrix();
    //EYE
    glPushMatrix();
    glDisable (GL_LIGHTING);
    glColor3f(0,0,0);
    glTranslatef(0,0.4,0.9);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f( 0.5,0 );
    glVertex2f( -0.5,0 );
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
    glPopMatrix();
    //HAND
    glPushMatrix();
    glRotatef(rot,0,0,1);
    glTranslatef(-0.8,-0.5,0);
    glScalef(1.1,0.3,0.9);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-rot,0,0,1);
    glTranslatef(0.8,-0.5,0);
    glScalef(1.1,0.3,0.9);
    glutSolidCube(1);
    glPopMatrix();
}

void Jump()
{
    if (moveX)
        ball_x += velocityX;
    velocityY += gravity;
    ball_y += velocityY;
    //Wave hand
    if(ball_y < ball_y+velocityY)
        rot= 90;
    else
        rot= -30;
    //STEPPING THE OBSTACLE STEP
    if(!gameover)
    {
        for(int i=0; i<step_y.size(); i++)
        {
            //collision detection
            if (velocityY < 0 && ball_y >= step_y[i]+2.5f+fall_y && ball_y <= step_y[i]+3.5f+fall_y && ball_x < step_x[i]+2.0f && ball_x > step_x[i]-2.0f)
            {
                velocityY = 0.048f;
                if(color>=1.0f || color <=0)
                    countercolor*=-1;
                color += countercolor;
                ball_y += velocityY;
                if(ball_y > Eye)
                    Eye = ball_y-0.09;
            }
        }
    }
}

void drawTitle()
{
    x_anim+=speed_anim;
    y_anim-=y_grav*2;
    counter+=1;
    if(y_anim<-17 && x_anim>-1.6)
    {
        y_anim+=4-(counter/1100);
    }
    if(y_anim<-18)
    {
        y_anim=-18;
        x_anim=-2.1;
    }

    glTranslatef(x_anim,y_anim,2);
    glScalef(0.008,0.008,1);
    glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char*)"G");
    glTranslatef(x_anim+10,y_anim+40,2);
    glutStrokeString(GLUT_STROKE_ROMAN,(unsigned char*)"L");
}

void EnemyCol()
{
    if (!gameover)
    {
        for (int i=0; i<enemy_x.size(); i++)
        {
            enemy_x[i]+=velocity_enemy;
            if(enemy_x[i]>=15.0f || enemy_x[i]<=-15.0f)
                velocity_enemy*=-1;
            if(ball_x>=enemy_x[i]-1.5f && ball_x<=enemy_x[i]+1.5 && ball_y>=enemy_y[i]+fall_y-1.0f&& ball_y<=enemy_y[i]+fall_y+3.0f)
                gameover=true;
        }
    }
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

void display()
{
    if(maks < ball_y)
        maks=ball_y;
    sprintf(buffer, "%.0f", maks*10);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(color, 0.5f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(camera <=Eye) camera+=0.03f;
    gluLookAt(0,camera+10,40.0, 0.0, camera+10, 0.0, 0,25, 0);
    //LIGHTING
    glPushMatrix ();
    GLfloat light_position1[] = { 0, 1000, 3000, 0.5};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glTranslated (0.0, 0.0, 1.5);
    glDisable (GL_LIGHTING);
    glEnable (GL_LIGHTING);
    glPopMatrix ();

    //PLAYER
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(ball_x,ball_y,0);
    drawPlayer();
    glPopMatrix();

    //obstacle
    glPushMatrix();
    glDisable (GL_LIGHTING);

//FIRST STEP
    glPushMatrix();
    glTranslatef(0,step_y[0]+fall_y,0);
    glScalef(3,1,0);
    glutSolidCube(1);
    glPopMatrix();
//
    fall_y -= 0.00043f;
//ADDITIONAL CONDITION
    if (start)
    {

        //TEXT
        glTranslatef(0,0,1);
        glColor3f(0,0,0);
        renderBitmapString(-14,25+camera, (void *)font, "Score : ");
        renderBitmapString(-10, 25+camera, (void *)font, buffer);
        glPopMatrix();
        //Blocka
        glColor3f(1,1,0);
        for(int i=0; i<step_y.size(); i++)
        {
            glPushMatrix();
            glTranslatef(step_x[i],(step_y[i]+fall_y),0);
            glScalef(3,1,0);
            glutSolidCube(1);
            glPopMatrix();
            if(step_y[i]+fall_y<camera-18)
            {
                step_x.push_back(Random(-10.0f,10.0f));
                step_y.push_back(step_y.back()+Random(6.0f,10.0f));
                step_x.erase(step_x.begin());
                step_y.erase(step_y.begin());
            }
        }
        //enemy
        for(int i=0; i<enemy_x.size(); i++)
        {
            glPushMatrix();
            glTranslatef(enemy_x[i],enemy_y[i]+fall_y,0);
            drawEnemy();
            glPopMatrix();
            if(enemy_y[i]+fall_y<camera-18.0)
            {
                enemy_x.push_back(Random(-10.0f,10.0f));
                enemy_y.push_back(enemy_y.back()+Random(15.0f,30.0f));
                enemy_x.erase(enemy_x.begin());
                enemy_y.erase(enemy_y.begin());
            }
        }
        //movement
        Jump();
        EnemyCol();
    }
    if(!start)
    {
        ball_x=0.5f, ball_y=0.0f;
        fall_y=0;
        camera=-30;
        glPushMatrix();
        glColor3f(0,0,0);
        renderBitmapString(-1,-18, (void *)font2, "JUMP");
        renderBitmapString(-4.75,-20, (void *)font, "Press F1 to start game");
        renderBitmapString(-5,-21, (void *)font, "Press END twice to exit");
        glPushMatrix();
        drawTitle();
        glPopMatrix();
        glPopMatrix();
        gluLookAt(0,-20,25.0, 0.0, -20, 0.0, 0,20, 0);
    }
    if(ball_y < camera-15.0f ) //game over
    {
        gameover=true;
        start=false;
    }
    if (gameover)
    {
        glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(0,0,1);
        renderBitmapString(-2,4+camera, (void *)font, "GAME OVER");
        renderBitmapString(-4,3+camera, (void *)font, "Press END to exit");
        renderBitmapString(-4.3,2+camera, (void *)font, "Press F1 to restart");
        glPopMatrix();
    }
    //glutPostRedisplay();
    glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, GLfloat(w)/GLfloat(h), 1.0, 1000.0);
}

void init()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(color, 0.5f, 1.0f, 0.0f);	// White Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    step_y[0]=-6.0f;
    step_x[0]=0;
    step_x[1]=Random(-12.0f,12.0f);
    step_y[1]=Random(0.0f,2.0f);
    enemy_y[0]=Random(10.0f,23.0f);
    for(int i=2; i<step_y.size(); i++)
    {
        step_x[i]=Random(-10.0f,10.0f);
        step_y[i]=step_y[i-1]+Random(6.0f,10.0f);
    }
    for(int i=1; i<enemy_x.size(); i++)
    {
        enemy_x[i]=Random(-15.0f,15.0f);
        enemy_y[i]=enemy_y[i-1]+Random(17.0f,50.0f);
    }
}

void Move(int key, int, int)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        moveX = true;
        velocityX= -0.020;
        break;
    case GLUT_KEY_RIGHT:
        moveX = true;
        velocityX = 0.020;
        break;
    case GLUT_KEY_F1:
        start=true;
        if (gameover)
        {
            init();
            gameover=false;
            Eye=ball_y=0;
            gravity = -0.000081f;
            fall_y=-0.00002f;
            ball_x=0;
            maks=0;
            camera=-20;
            color=0.01f;
        }
        break;
    case GLUT_KEY_END:
        exit(0);
        break;
    default:
        break;
    }
    //glutPostRedisplay();
}

void Stop(int key, int, int)
{
    if(key==GLUT_KEY_LEFT || key==GLUT_KEY_RIGHT)
    {
        moveX = false;
        velocityX=0;
    }
    glutPostRedisplay();
}

void Timer (int time)
{

    glutPostRedisplay();
    glutTimerFunc(1, Timer,0);
}
int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 10);
    glutInitWindowSize(600, 650);
    glutCreateWindow("GLJUMP");

    glutReshapeFunc(reshape);
    glutSpecialFunc(Move);
    glutSpecialUpFunc(Stop);
    glutDisplayFunc(display);
    Timer(0);
    init();
    glutMainLoop();
}
