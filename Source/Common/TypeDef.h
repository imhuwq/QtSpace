#ifndef QTSPACE_TYPEDEF_H
#define QTSPACE_TYPEDEF_H

#include <memory>

#include <QTime>
#include <QTimer>
#include <QObject>
#include <QString>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

using namespace std;

#define DEF_SHR_PTR(cls) typedef shared_ptr<cls> cls##Ptr;\
                         typedef shared_ptr<const cls> k##cls##Ptr

#define DEF_SHR_PTR_ALIAS(cls, alias) typedef shared_ptr<cls> alias##Ptr;\
                                      typedef shared_ptr<const cls> k##alias##Ptr

#define DEF_WEK_PTR(cls) typedef weak_ptr<cls> w##cls##Ptr;\
                         typedef weak_ptr<const cls> wk##cls##Ptr

#define DEF_WEK_PTR_ALIAS(cls, alias) typedef weak_ptr<cls> w##alias##Ptr;\
                                      typedef weak_ptr<const cls> wk##alias##Ptr

#define DEF_PTR(cls) DEF_SHR_PTR(cls); DEF_WEK_PTR(cls)

#define DEF_PTR_ALIAS(cls, alias) DEF_SHR_PTR_ALIAS(cls, alias); DEF_WEK_PTR_ALIAS(cls, alias)

#define DEF_CLS(cls) class cls; DEF_SHR_PTR(cls); DEF_WEK_PTR(cls)

// Lib - Qt
DEF_PTR(QTime);
DEF_PTR(QTimer);
DEF_PTR(QOpenGLTexture);
DEF_PTR(QOpenGLFunctions);
DEF_PTR_ALIAS(QOpenGLBuffer, QGLVBO);
DEF_PTR_ALIAS(QOpenGLVertexArrayObject, QGLVAO);
DEF_PTR_ALIAS(QOpenGLShaderProgram, QGLShader);

// Application
DEF_CLS(Application);

DEF_CLS(MainWindow);

// Control
DEF_CLS(State);

DEF_CLS(Controller);

// GLRender
DEF_CLS(SceneAnimator);

DEF_CLS(MeshInstanceRender);

DEF_CLS(SceneRender);

DEF_CLS(MainLoop);

// IO
DEF_CLS(FbxFileLoader);

DEF_CLS(ModelFileLoader);

DEF_CLS(VertexContext);

DEF_CLS(VertexPack);

DEF_CLS(VertexTable);

// Resource
DEF_CLS(Material);

DEF_CLS(Mesh);

DEF_CLS(Model);

DEF_CLS(Resource);

DEF_CLS(Scene);

DEF_CLS(Texture);

DEF_CLS(VertexSemantic);

DEF_CLS(Camera);

DEF_CLS(MeshInstance);

DEF_CLS(Node);

DEF_CLS(DirectionalLight);

DEF_CLS(DotLight);

DEF_CLS(Light);

DEF_CLS(SpotLight);

#endif // QTSPACE_TYPEDEF_H