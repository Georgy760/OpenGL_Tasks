#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265359f;

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

// Функция для отрисовки правильного пятиугольника
void drawPolygon() {
    const int numVertices = 5; // Число вершин пятиугольника
    const float radius = 3.0f;  // Радиус описанной окружности
    float angleStep = 2 * PI / numVertices; // Угол между вершинами

    glBegin(GL_POLYGON);

    for (int i = 0; i < numVertices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Устанавливаем нормали для каждой вершины (для освещения)
        glNormal3f(x, y, 1.0f);

        // Устанавливаем цвет для каждой вершины
        glColor3f((i % 3 == 0) ? 1.0f : 0.0f, (i % 3 == 1) ? 1.0f : 0.0f, (i % 3 == 2) ? 1.0f : 0.0f);

        // Устанавливаем вершины
        glVertex3f(x, y, 0.0f);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включаем цвет вершин
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0); // Камера в точке (20, 20, 20)

    // Рисуем правильный пятиугольник
    drawPolygon();

    // Отключаем цвет вершин
    glDisable(GL_COLOR_MATERIAL);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Regular Pentagon");

    init();

    glutDisplayFunc(display);

    glutIdleFunc([]() {
        glutPostRedisplay();
    });

    glutMainLoop();

    return 0;
}
