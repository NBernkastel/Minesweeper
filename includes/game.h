#define _CRT_SECURE_NO_WARNINGS // чтобы vs не жаловалс€
#include <glew.h> // граф библиотека
#include <glfw3.h>// граф библиотека
#include <time.h>//врем€ 
#include <windows.h>//api винды вообщем based 
#define STB_IMAGE_IMPLEMENTATION // не знаю зачем, но нужно дл€ библиотки снизу
#include <stb_image.h> // открывает изображение большенства форматов ( удобна€ библиотека дл€ текстурировани€)
GLFWwindow* window; // а тут окно создаем 
int m_press = 0; // когда лкм нажат то 1, когда пкм 2
int gamemode = 0; // режим игры 
double xpos, ypos; // кординаты мыши (по пиксил€м)
int gameover = 0; // состо€ние игры
float sdwg;// сдвиг, нужен чтобы все красиво по центру было
struct square // структура квадратов
{
    int is_open; // открытое/закрытое состо€ние клеток
    int min;// эта клетка мина?
    int bombs_around; // бомбы вокруг клетки
    int flag;// стоит ли флаг
    float color;// изменение цвета клетки
    int close;
}; struct square field[15][15]; // игровое поле
int texturs [5]; // текстуры
float colorchange[] = { 1,1,1,1 }; // изменение цвета кнопок в меню
int refresh = 0; // игра заново
int flag_stay = 0; // колво сто€щих флагов
int m_press_first = 0; // было ли первое нажатие в игре
int FHIGHT; // насто€ща€ высота пол€
int FLENGHT;// насто€ща€ длина пол€
int whenhelp = 0;
int mincounter;
///функции
void helpmin();
void saveload();
void save();