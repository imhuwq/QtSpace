#include <QQuaternion>
#include <QVector3D>

int main() {
    QVector3D target(0, 0, 0);
    QVector3D position(0, 0, 25);
    float distance = 25.0f;
    
    QVector3D separate_1 = QVector3D(2, 6, 0);
    QVector3D separate_2 = QVector3D(3, 3, 0);
    QVector3D all = separate_1 + separate_2;
    
};