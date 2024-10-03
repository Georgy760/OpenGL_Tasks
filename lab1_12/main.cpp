#include <GL/glut.h>
#include <cmath>

// Функция для инициализации OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Цвет фона: черный
    glEnable(GL_DEPTH_TEST); // Включаем буфер глубины
    glEnable(GL_LIGHTING); // Включаем освещение
    glEnable(GL_LIGHT0); // Включаем источник света 0

    // Направление источника света (параллельно вектору {1, 1, 1})
    GLfloat lightDirection[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Настройка перспективной проекции
}

// Функция для отрисовки трапеции
void drawTrapezoid() {
    glBegin(GL_QUADS);

    // Вершина 1 (нижняя левая) - цвет красный
    glNormal3f(0.0, 0.0, 1.0); // Нормаль направлена вперед
    glColor3f(1.0, 0.0, 0.0); // Красный цвет
    glVertex3f(0.0, -4.0, 0.0); // Нижняя левая вершина по оси OY

    // Вершина 2 (верхняя левая) - цвет зеленый
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); // Зеленый цвет
    glVertex3f(0.0, 4.0, 0.0); // Верхняя левая вершина по оси OY

    // Вершина 3 (верхняя правая) - цвет синий
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0); // Синий цвет
    glVertex3f(5.0, 2.0, 0.0); // Верхняя правая вершина

    // Вершина 4 (нижняя правая) - цвет желтый
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 0.0); // Желтый цвет
    glVertex3f(5.0, -2.0, 0.0); // Нижняя правая вершина

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включаем цвет вершин
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Рисуем трапецию
    drawTrapezoid();

    // Отключаем цвет вершин
    glDisable(GL_COLOR_MATERIAL);

    // Устанавливаем камеру (камера в точке (20, 20, 20), направлена в начало координат)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Trapezoid with Lighting");

    init();

    glutDisplayFunc(display);

    glutIdleFunc([]() {
        glutPostRedisplay();
    });

    glutMainLoop();

    return 0;
}
