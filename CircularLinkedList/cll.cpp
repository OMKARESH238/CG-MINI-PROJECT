#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

void display();
void drawstring(float x, float y, char *string, int col, int drawstringflag);


struct node
{
    int info;
    struct node *link;
};
struct node *head;

struct arr
{
    int p;
    int q;
}ar[20];


typedef struct node* NODE;
static NODE first;
static int count = 0,  flag = 1;
int succ = 1, succ1 = 1, ins_succ = 1;
int choice, item, key;
float color[4][3] = {{1.0, 1.0, 1.0}, {0.8, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.8}};
int drawstringflag = 0, printflag = 1, titleflag = 1;


NODE getnode()
{
    NODE x;
    x = (NODE)malloc(sizeof(struct node));
    if(x == NULL)
    {
            printf("Insufficient memory!!\n");
            exit(0);
    }
    return x;
}

NODE  insert_front(int item, NODE first)
{
    NODE temp;
    temp = getnode();
    temp->info = item;
    temp->link = first;
    return temp;
}

NODE insert_rear(int item, NODE first)
{
    NODE temp;
    NODE cur;
    temp = getnode();
    temp->info = item;
    temp->link = NULL;
    if(first == NULL)
    return temp;
    cur = first;
    while(cur->link != NULL)
        cur = cur->link;
    cur->link = temp;
    return first;
}

NODE delete_front(NODE first)
{
    NODE temp;
    if(first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
    temp = first;
    temp = temp->link;
    printf("Deleted item from front =  %d \n", first->info);
    free(first);
    return temp;
}

NODE delete_rear(NODE first)
{
    NODE cur, prev;
    if(first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
        if(first->link == NULL)
    {
        printf("Item to be deleted is %d \n", first->info);
        free(first);
        return NULL;
    }
    prev = NULL;
    cur = first;
    while(cur->link != NULL)
    {
        prev = cur;
        cur = cur->link;
    }
    printf("Deleted item from rear =  %d \n", cur->info);
    free(cur);
    prev->link = NULL;
    return first;
}

void cll_menu(int choice)
{
    switch(choice)
    {
        case 1:
            printf("Enter the item to be inserted at front: ");
            scanf("%d", &item);
            first = insert_front(item, first);
            count++;
            display();
            break;
        case 2:
            printf("Enter the item to be inserted at rear: ");
            scanf("%d", &item);
            first = insert_rear(item, first);
            count++;
            display();
            break;
        case 3:
            succ = 1;
            first = delete_front(first);
            count--;
            display();
            break;
        case 4:
            succ = 1;
            first = delete_rear(first);
            count--;
            display();
            break;
        case 5:
            exit(0);
    }
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawstring(float x, float y, char *string, int col, int drawstringflag)
{
    char *c;
    glColor3fv(color[col]);
    glRasterPos2f(x, y);
    if (drawstringflag == 0)
    {
        for(c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    else if (drawstringflag == 1)
    {
        for(c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    else
    {
        for(c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void title()
{
    glClearColor(192.0, 192.0, 192.0, 1.0);
    drawstring(105.0, 440.0, (char *)"AJ Institute of Engineering and Technology", 1, 2);
    drawstring(200.0, 410.0, (char *)"Kottara Chowki , Mangaluru", 1, 0);
    drawstring(160.0, 360.0, (char *)"Circular Linked List Visualizer", 1, 2);
    drawstring(15.0, 300.0, (char *)"Submitted by :", 0, 0);
    drawstring(105.0, 250.0, (char *)"Sirius Thomas Mathew       4JK18CS028", 0, 0);
    drawstring(105.0, 220.0, (char *)"Omkaresh      4JK18CS029", 0, 0);
    drawstring(200.0, 160.0, (char *)"Under the Guidance of", 3, 2);
    drawstring(145.0, 130.0, (char *)" Mr. Vijaykumar Dudhanikar", 0, 0);
    drawstring(245.0, 110.0, (char *)"Assistant Professor", 0, 1);
    drawstring(175.0, 90.0, (char *)"Department of Computer Science & Engineerig", 0, 1);
    drawstring(15.0, 40.0, (char *)"Click Right Mouse Button for operations menu", 3, 0);
    glFlush();
}

void display()
{
    if(titleflag)
    {
        title();
        titleflag = 0;
    }
    int i = 0, j = 0, k = 0, b[20];
    NODE temp;
    glClearColor(192.0, 192.0, 192.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.6);
    drawstring(200.0, 450.0, (char *)"CIRCULAR LINKED LIST", 3, 0);
    if(first == NULL)
    {
        if(printflag)
        {
            printf("\nEmpty List\n");
            printflag = 0;
        }
    }
    temp = first;
    while(temp != NULL)
    {
        for(k = 0;k < count;k++)
        {
            GLfloat x1 = 50, y1 = 200, x2 = 80, y2 = 225;
            GLfloat x3 = 110, y3 = 250, x4 = 95, y4 = 225;
            GLfloat x5 = 160, y5 = 210, y6 = 240, x6 = 180;
            GLfloat y0 = 150, x0 = 30, x00 = 40;
            int pos = 130;
            if(temp->link == NULL)
            {
                glColor3f(0.0, 0.0, 0.70);
                glBegin(GL_POLYGON);
                    glVertex2i(x1+k*pos, y1);
                    glVertex2i(x1+k*pos, y3);
                    glVertex2i(x2+k*pos, y3);
                    glVertex2i(x2+k*pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON);
                    glVertex2i(x2+k*pos, y1);
                    glVertex2i(x2+k*pos, y3);
                    glVertex2i(x3+k*pos, y3);
                    glVertex2i(x3+k*pos, y1);
                glEnd();
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_LINES);
                    glVertex2i(x4+k*pos, y4);
                    glVertex2i(x5+k*pos, y4);
                    glVertex2i(x5+k*pos, y4);
                    glVertex2i(x5+k*pos, y0);
                    glVertex2i(x5+k*pos, y0);
                    glVertex2i(x0, y0);
                    glVertex2i(x0, y0);
                    glVertex2i(x0, y4);
                    glVertex2i(x0, y4);
                    glVertex2i(x1, y4);
                glEnd();
                glBegin(GL_LINES);
                    glVertex2i(x00, y6);
                    glVertex2i(x1, y4);
                    glVertex2i(x1, y4);
                    glVertex2i(x00, y5);
                glEnd();
            }
            else
            {
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_LINES);
                    glVertex2i(x4+k*pos, y4);
                    glVertex2i(x6+k*pos, y4);
                glEnd();
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_LINES);
                    glVertex2i(x5+k*pos, y6);
                    glVertex2i(x6+k*pos, y4);
                    glVertex2i(x6+k*pos, y4);
                    glVertex2i(x5+k*pos, y5);
                glEnd();
                glColor3f(0.0, 0.0, 0.70);
                glBegin(GL_POLYGON);
                    glVertex2i(x1+k*pos, y1);
                    glVertex2i(x1+k*pos, y3);
                    glVertex2i(x2+k*pos, y3);
                    glVertex2i(x2+k*pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON);
                    glVertex2i(x2+k*pos, y1);
                    glVertex2i(x2+k*pos, y3);
                    glVertex2i(x3+k*pos, y3);
                    glVertex2i(x3+k*pos, y1);
                glEnd();
            }
            b[j] = temp->info;
            temp = temp->link;
            ar[i].p = b[j]/10;
            ar[i].q = b[j]%10;
            ar[i].p = ar[i].p+48;
            ar[i].q = ar[i].q+48;
            glColor3f(1.0, 1.0, 0.0);
            glRasterPos2f(55.0+k*pos, 215.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].p);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].q);
            drawstring(50.0+k*pos, 185, (char *)"INFO", 1, 1);
            drawstring(85.0+k*pos, 185, (char *)"LINK", 1, 1);
            i++;
            j++;
            glFlush();
        }
    }
}

int main(int argc, char** argv)
{
    printf("                     CIRCULAR LINKED LIST                       \n\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circular Linked List Visualizer");
    glutCreateMenu(cll_menu);
    glutAddMenuEntry("Insert at Front", 1);
    glutAddMenuEntry("Insert at Rear", 2);
    glutAddMenuEntry("Delete from Front", 3);
    glutAddMenuEntry("Delete from Rear", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
