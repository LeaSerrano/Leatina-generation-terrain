#ifndef MYVIEWER_H
#define MYVIEWER_H

#include "point3.h"

// Parsing:
#include "BasicIO.h"

// opengl and basic gl utilities:
#define GL_GLEXT_PROTOTYPES
#include <gl/openglincludeQtComp.h>
#include <GL/glext.h>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFunctions>
#include <QGLViewer/qglviewer.h>

#include <gl/GLUtilityMethods.h>
#include <QGLViewer/manipulatedCameraFrame.h>

// Qt stuff:
#include <QFormLayout>
#include <QToolBar>
#include <QColorDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QInputDialog>
#include <QLineEdit>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QtMath>
#include <algorithm>


#include "qt/QSmartAction.h"
#include "terrainMesh.h"

#include <fstream>
#include <sstream>
#include <algorithm>


class MyViewer : public QGLViewer , public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

    QWidget * controls;

    GLuint shaderProgram;
    GLuint vertexShader, fragmentShader;
    QMatrix4x4 modelMatrix;

<<<<<<< HEAD
=======
    QPoint lastMousePos;
    qglviewer::Vec accumulatedMouseTranslation;
    qglviewer::Vec accumulatedKeyTranslation;

    qglviewer::Quaternion accumulatedRotationX;
    qglviewer::Quaternion accumulatedRotationY;



>>>>>>> 73e4220c39e58f6db3e6ca0bee8c920f69108e5a
public :
    TerrainMesh terrainMesh;

    enum Vue { VueTerrain, VuePremierePersonne };
    Vue vueActuelle;

    MyViewer(QGLWidget * parent = NULL) : QGLViewer(parent) , QOpenGLFunctions_4_3_Core() {
        vueActuelle = VueTerrain;
    }



    void add_actions_to_toolBar(QToolBar *toolBar)
    {
        // Specify the actions :
        DetailedAction * open_mesh = new DetailedAction( QIcon("./icons/open.png") , "Open Mesh" , "Open Mesh" , this , this , SLOT(open_mesh()) );
        DetailedAction * save_mesh = new DetailedAction( QIcon("./icons/save.png") , "Save model" , "Save model" , this , this , SLOT(save_mesh()) );
        DetailedAction * help = new DetailedAction( QIcon("./icons/help.png") , "HELP" , "HELP" , this , this , SLOT(help()) );
        DetailedAction * saveCamera = new DetailedAction( QIcon("./icons/camera.png") , "Save camera" , "Save camera" , this , this , SLOT(saveCamera()) );
        DetailedAction * openCamera = new DetailedAction( QIcon("./icons/open_camera.png") , "Open camera" , "Open camera" , this , this , SLOT(openCamera()) );
        DetailedAction * saveSnapShotPlusPlus = new DetailedAction( QIcon("./icons/save_snapshot.png") , "Save snapshot" , "Save snapshot" , this , this , SLOT(saveSnapShotPlusPlus()) );

        // Add them :
        toolBar->addAction( open_mesh );
        toolBar->addAction( save_mesh );
        toolBar->addAction( help );
        toolBar->addAction( saveCamera );
        toolBar->addAction( openCamera );
        toolBar->addAction( saveSnapShotPlusPlus );
    }

    GLuint loadTexture(const QString& filePath)
    {
        // Charger l'image avec QImage
        QImage image(filePath);

        if (image.isNull()) {
            qDebug() << "Failed to load texture: " << filePath;
            return 0;  // Retourner 0 en cas d'échec du chargement de l'image
        }

        // Convertir l'image en format adapté à OpenGL
        image = image.convertToFormat(QImage::Format_RGBA8888);

        // Générer une texture OpenGL
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Paramètres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Charger les données de l'image dans la texture
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            image.width(),
            image.height(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image.bits()
            );

        // Générer les mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Désactiver la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        return textureID;
    }

    void drawBuffers() {
        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.vertex_buffer.size() * sizeof(QVector3D), &terrainMesh.vertex_buffer[0], GL_STATIC_DRAW);

        GLuint indexbuffer;
        glGenBuffers(1, &indexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, indexbuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.index_buffer.size() * sizeof(short), &terrainMesh.index_buffer[0], GL_STATIC_DRAW);

        GLuint normalBuffer;
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.normal_buffer.size() * sizeof(float), &terrainMesh.normal_buffer[0], GL_STATIC_DRAW);

        //Texture
        GLuint textureCoordBuffer;
        glGenBuffers(1, &textureCoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, textureCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.texture_coord_buffer.size() * sizeof(QVector2D), &terrainMesh.texture_coord_buffer[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

<<<<<<< HEAD
        //Texture
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, textureCoordBuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
=======
>>>>>>> 73e4220c39e58f6db3e6ca0bee8c920f69108e5a

        // Charger les textures
        GLuint textureEauID = loadTexture("./images/textureEau.jpg");
        GLuint textureHerbeID = loadTexture("./images/textureHerbe.jpg");
        GLuint textureRocheID = loadTexture("./images/textureRoche.jpg");
        GLuint textureNeigeID = loadTexture("./images/textureNeige.jpg");
        GLuint textureHeightmapID = loadTexture("perlinNoise.png");

        QString vertexShaderSource = readShaderFile("src/vshader.glsl");
        QString fragmentShaderSource = readShaderFile("src/fshader.glsl");

        shaderProgram = createShaderProgram(vertexShaderSource.toUtf8().constData(), fragmentShaderSource.toUtf8().constData());

        //Texture
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureEau"), 0);     // Associer la texture à l'unité de texture 0
        glUniform1i(glGetUniformLocation(shaderProgram, "textureHerbe"), 1);   // Associer la texture à l'unité de texture 1
        glUniform1i(glGetUniformLocation(shaderProgram, "textureRoche"), 2);   // Associer la texture à l'unité de texture 2
        glUniform1i(glGetUniformLocation(shaderProgram, "textureNeige"), 3);   // Associer la texture à l'unité de texture 3
        glUniform1i(glGetUniformLocation(shaderProgram, "textureHeightmap"), 4);
        glUseProgram(0);

        // Associer les textures aux unités de texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureEauID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureHerbeID);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureRocheID);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textureNeigeID);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, textureHeightmapID);
    }

    void drawTerrainView() {
            drawBuffers();
    }

    void drawPremierePersonneView() {
            float centerX = terrainMesh.sizeX / 2.0f;
            float centerZ = terrainMesh.sizeZ / 2.0f;

            float stepX = static_cast<float>(terrainMesh.sizeX) / static_cast<float>(terrainMesh.resolution);
            float stepZ = static_cast<float>(terrainMesh.sizeZ) / static_cast<float>(terrainMesh.resolution);

            int i = static_cast<int>(centerX / stepX);
            int j = static_cast<int>(centerZ / stepZ);

            float perlin = terrainMesh.perlinNoise->getPerlinAt(i, j, terrainMesh.resolution);
            GLfloat centerY;
            terrainMesh.getHeightAtPerlinPx(centerY, perlin);

            qglviewer::Vec cameraPosition(centerX, centerY+0.2f, centerZ);
            camera()->setSceneRadius(terrainMesh.sizeX * 2.0);
            camera()->setPosition(cameraPosition);

            drawBuffers();

            animate();
    }

    void setCameraPositionWithPerlinHeight() {
            qglviewer::Vec cameraPosition = camera()->position();

            float stepX = static_cast<float>(terrainMesh.sizeX) / static_cast<float>(terrainMesh.resolution);
            float stepZ = static_cast<float>(terrainMesh.sizeZ) / static_cast<float>(terrainMesh.resolution);

            int i = static_cast<int>(cameraPosition.x / stepX);
            int j = static_cast<int>(cameraPosition.z / stepZ);

            float perlin = terrainMesh.perlinNoise->getPerlinAt(i, j, terrainMesh.resolution);
            GLfloat centerY;
            terrainMesh.getHeightAtPerlinPx(centerY, perlin);

            cameraPosition.y = centerY+ 0.2f;
            camera()->setPosition(cameraPosition);
    }

    void draw() {
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, modelMatrix.data());

        GLfloat projectionMatrix[16];
        camera()->getProjectionMatrix(projectionMatrix);
        GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);

        GLfloat viewMatrix[16];
        camera()->getModelViewMatrix(viewMatrix);

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMatrix);


        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.5, 0.5, 0.5);
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0, 1.0, 1.0);
        glUniform3f(glGetUniformLocation(shaderProgram, "ambientMaterial"), 0.2, 0.2, 0.2);
        glUniform3f(glGetUniformLocation(shaderProgram, "diffuseMaterial"), 0.5, 0.5, 0.5);
        glUniform3f(glGetUniformLocation(shaderProgram, "specularMaterial"), 0.3, 0.3, 0.3);
        glUniform1f(glGetUniformLocation(shaderProgram, "shininessMaterial"), 0.2);

        qglviewer::Vec cameraPosition = camera()->position();
        glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), cameraPosition[0], cameraPosition[1], cameraPosition[2]);

        qglviewer::Vec cameraView = camera()->viewDirection();
        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), cameraView[0], cameraView[1], cameraView[2]);

        if (vueActuelle == VueTerrain) {
            drawTerrainView();
        } else if (vueActuelle == VuePremierePersonne) {
            drawPremierePersonneView();
        }


        glEnable(GL_DEPTH_TEST);
        glEnable( GL_LIGHTING );

        glDrawElements(GL_TRIANGLES, terrainMesh.index_buffer.size(), GL_UNSIGNED_SHORT, (void*)0);

        glUseProgram(0);
    }

    void pickBackgroundColor() {
        QColor _bc = QColorDialog::getColor( this->backgroundColor(), this);
        if( _bc.isValid() ) {
            this->setBackgroundColor( _bc );
            this->update();
        }
    }

    void adjustCamera(point3d const & bb, point3d const & BB) {
        point3d const & center = (bb + BB) / 2.f;
        setSceneCenter(qglviewer::Vec(center[0], center[1], center[2]));
        setSceneRadius(0.5f * (BB - bb).norm());
        camera()->setPosition(qglviewer::Vec(center[0], center[1], center[2] - 2.0 * (BB - bb).norm()));

        showEntireScene();
    }


    GLuint compileShader(const char* shaderSource, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            qDebug() << "Shader compilation error:\n" << infoLog;
            return 0;
        }

        return shader;
    }

    GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
        GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            qDebug() << "Shader program linking error:\n" << infoLog;
            return 0;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

    QString readShaderFile(const char* filePath) {

        std::ifstream file(filePath);
        if (!file.is_open()) {
            qDebug() << "Unable to open file: " << filePath;
            return QString();
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return QString::fromStdString(buffer.str());
    }


    void init() {
        makeCurrent();
        initializeOpenGLFunctions();

        setBackgroundColor(QColor(20, 20, 20));

        // Lights:
        GLTools::initLights();
        //GLTools::setSunsetLight();
        //GLTools::setDefaultMaterial();

        //
        glShadeModel(GL_SMOOTH);
        glFrontFace(GL_CCW); // CCW ou CW

        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CLIP_PLANE0);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_COLOR_MATERIAL);

        //

        point3d bbmin(0.0, 0.0, 0.0) , BBmax(1, 1, 1);
        adjustCamera(bbmin, BBmax);

        modelMatrix = QMatrix4x4();
    }

    QString helpString() const {
        QString text("<h2>Our cool project</h2>");
        text += "<p>";
        text += "This is a research application, it can explode.";
        text += "<h3>Participants</h3>";
        text += "<ul>";
        text += "<li>...</li>";
        text += "</ul>";
        text += "<h3>Basics</h3>";
        text += "<p>";
        text += "<ul>";
        text += "<li>H   :   make this help appear</li>";
        text += "<li>Ctrl + mouse right button double click   :   choose background color</li>";
        text += "<li>Ctrl + T   :   change window title</li>";
        text += "</ul>";
        return text;
    }

    void updateTitle( QString text ) {
        this->setWindowTitle( text );
        emit windowTitleUpdated(text);
    }

    void keyPressEvent( QKeyEvent * event ) {

            if( event->key() == Qt::Key_H ) {
                help();
            }
            else if( event->key() == Qt::Key_T ) {
                if( event->modifiers() & Qt::CTRL )
                {
                    bool ok;
                    QString text = QInputDialog::getText(this, tr(""), tr("title:"), QLineEdit::Normal,this->windowTitle(), &ok);
                    if (ok && !text.isEmpty())
                    {
                        updateTitle(text);
                    }
                }
            }

            if (vueActuelle == VueTerrain) {
                if (event->key() == Qt::Key_Left) {
                    rotateObjectLeft();
                }
                else if (event->key() == Qt::Key_Right) {
                    rotateObjectRight();
                }
                else if (event->key() == Qt::Key_Up) {
                    rotateObjectUp();
                }
                else if (event->key() == Qt::Key_Down) {
                    rotateObjectDown();
                }
            }
            else if (vueActuelle == VuePremierePersonne) {

                const float stepSize = 1.f/terrainMesh.resolution;
                const float stepRotate = 0.05f;

                if (event->key() == Qt::Key_Q) {
                    accumulatedKeyTranslation += qglviewer::Vec(-stepSize, 0, 0);

                } else if (event->key() == Qt::Key_D) {
                    accumulatedKeyTranslation += qglviewer::Vec(stepSize, 0, 0);

                } else if (event->key() == Qt::Key_Z) {
                    accumulatedKeyTranslation += qglviewer::Vec(0, 0, -stepSize);

                } else if (event->key() == Qt::Key_S) {
                    accumulatedKeyTranslation += qglviewer::Vec(0, 0, stepSize);
                }
                else if (event->key() == Qt::Key_Up) {
                    qreal pitch = camera()->viewDirection().y;

                    if (pitch <= 0.4) {
                        qglviewer::Quaternion rotation;
                        rotation.setAxisAngle(qglviewer::Vec(1.0, 0.0, 0.0), stepRotate);
                        camera()->frame()->rotate(rotation);
                    }
                }
                else if (event->key() == Qt::Key_Down) {
                    qreal pitch = camera()->viewDirection().y;

                    if (pitch >= -0.7) {
                        qglviewer::Quaternion rotation;
                        rotation.setAxisAngle(qglviewer::Vec(-1.0, 0.0, 0.0), stepRotate);
                        camera()->frame()->rotate(rotation);
                    }
                }
                else if (event->key() == Qt::Key_Right) {
                    qglviewer::Quaternion rotation;
                    rotation.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), stepRotate);
                    camera()->frame()->rotate(rotation);
                }
                else if (event->key() == Qt::Key_Left) {
                    qglviewer::Quaternion rotation;
                    rotation.setAxisAngle(qglviewer::Vec(0.0, 1.0, 0.0), stepRotate);
                    camera()->frame()->rotate(rotation);
                }

                update();

            }

    }

    void rotateObjectLeft() {
        GLfloat angle = 5.0f;
        QMatrix4x4 rotationMatrix;
        rotationMatrix.rotate(angle, 0.0f, 1.0f, 0.0f);
        applyRotation(rotationMatrix);
    }

    void rotateObjectRight() {
        GLfloat angle = -5.0f;
        QMatrix4x4 rotationMatrix;
        rotationMatrix.rotate(angle, 0.0f, 1.0f, 0.0f);
        applyRotation(rotationMatrix);
    }

    void rotateObjectUp() {
        GLfloat angle = 5.0f;
        QMatrix4x4 rotationMatrix;
        rotationMatrix.rotate(angle, 1.0f, 0.0f, 0.0f);
        applyRotation(rotationMatrix);
    }

    void rotateObjectDown() {
        GLfloat angle = -5.0f;
        QMatrix4x4 rotationMatrix;
        rotationMatrix.rotate(angle, 1.0f, 0.0f, 0.0f);
        applyRotation(rotationMatrix);
    }

    void applyRotation(const QMatrix4x4& rotationMatrix) {
        QVector3D objectCenter(0.5, 0.5, 0.5);

        QMatrix4x4 translationMatrix;
        translationMatrix.translate(objectCenter);
        modelMatrix = translationMatrix * rotationMatrix * translationMatrix.inverted() * modelMatrix;

        update();
    }

    void mousePressEvent(QMouseEvent *e) {

    }

    void mouseMoveEvent(QMouseEvent *e) {

    }

    void mouseReleaseEvent(QMouseEvent* e) {
    }

    void animate() {
        qglviewer::Vec cameraPosition = camera()->position() + accumulatedKeyTranslation;

        if (cameraPosition.x <= terrainMesh.sizeX && cameraPosition.x >= 0.0 && cameraPosition.z <= terrainMesh.sizeZ && cameraPosition.z >= 0.0) {
            camera()->setPosition(cameraPosition);
            setCameraPositionWithPerlinHeight();
        }
    }

signals:
    void windowTitleUpdated( const QString & );

public slots:
    void showControls()
    {
        // Show controls :
        controls->close();
        controls->show();
    }

    void saveCameraInFile(const QString &filename){
        std::ofstream out (filename.toUtf8());
        if (!out)
            exit (EXIT_FAILURE);
        // << operator for point3 causes linking problem on windows
        out << camera()->position()[0] << " \t" << camera()->position()[1] << " \t" << camera()->position()[2] << " \t" " " <<
                                          camera()->viewDirection()[0] << " \t" << camera()->viewDirection()[1] << " \t" << camera()->viewDirection()[2] << " \t" << " " <<
                                          camera()->upVector()[0] << " \t" << camera()->upVector()[1] << " \t" <<camera()->upVector()[2] << " \t" <<" " <<
                                          camera()->fieldOfView();
        out << std::endl;

        out.close ();
    }

    void openCameraFromFile(const QString &filename){

        std::ifstream file;
        file.open(filename.toStdString().c_str());

        qglviewer::Vec pos;
        qglviewer::Vec view;
        qglviewer::Vec up;
        float fov;

        file >> (pos[0]) >> (pos[1]) >> (pos[2]) >>
                                                    (view[0]) >> (view[1]) >> (view[2]) >>
                                                                                           (up[0]) >> (up[1]) >> (up[2]) >>
                                                                                                                            fov;

        camera()->setPosition(pos);
        camera()->setViewDirection(view);
        camera()->setUpVector(up);
        camera()->setFieldOfView(fov);

        camera()->computeModelViewMatrix();
        camera()->computeProjectionMatrix();

        update();
    }


    void openCamera(){
        QString fileName = QFileDialog::getOpenFileName(NULL,"","*.cam");
        if ( !fileName.isNull() ) {                 // got a file name
            openCameraFromFile(fileName);
        }
    }
    void saveCamera(){
        QString fileName = QFileDialog::getSaveFileName(NULL,"","*.cam");
        if ( !fileName.isNull() ) {                 // got a file name
            saveCameraInFile(fileName);
        }
    }

    void saveSnapShotPlusPlus(){
        QString fileName = QFileDialog::getSaveFileName(NULL,"*.png","");
        if ( !fileName.isNull() ) {                 // got a file name
            setSnapshotFormat("PNG");
            setSnapshotQuality(100);
            saveSnapshot( fileName );
            saveCameraInFile( fileName+QString(".cam") );
        }
    }
};




#endif // MYVIEWER_H
