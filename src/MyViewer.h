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

    QPoint lastMousePos;
    qglviewer::Vec accumulatedMouseTranslation;
    qglviewer::Vec accumulatedKeyTranslation;

    qglviewer::Quaternion accumulatedRotationX;
    qglviewer::Quaternion accumulatedRotationY;



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


        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);


        QString vertexShaderSource = readShaderFile("src/vshader.glsl");
        QString fragmentShaderSource = readShaderFile("src/fshader.glsl");

        shaderProgram = createShaderProgram(vertexShaderSource.toUtf8().constData(), fragmentShaderSource.toUtf8().constData());
    }

    void drawTerrainView() {
            drawBuffers();
    }

    void drawPremierePersonneView() {
        float centerX = terrainMesh.sizeX / 2.0f;
        float centerZ = terrainMesh.sizeZ / 2.0f;

        float perlin = terrainMesh.perlinNoise->getPerlinAt(centerX, centerZ, terrainMesh.resolution);
        GLfloat centerY;
        terrainMesh.getHeightAtPerlinPx(centerY, perlin);

        qglviewer::Vec cameraPosition(centerX, centerY + 1.0f, centerZ);
        camera()->setSceneRadius(terrainMesh.sizeX * 2.0);
        camera()->setPosition(cameraPosition);

        drawBuffers();

        animate();
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
        glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), /*0.0, 3.0, -7.0*/ cameraView[0], cameraView[1], cameraView[2]);

        //drawBuffers();

        if (vueActuelle == VueTerrain) {
            drawTerrainView();
        } else if (vueActuelle == VuePremierePersonne) {
            drawPremierePersonneView();
        }


        glEnable(GL_DEPTH_TEST);
        glEnable( GL_LIGHTING );

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, terrainMesh.index_buffer.size(), GL_UNSIGNED_SHORT, (void*)0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //update();

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

        // Check for compilation errors (you might want to add more detailed error checking)
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

        // Check for linking errors (you might want to add more detailed error checking)
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
            return QString();  // Return an empty QString
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        // Convert the std::string to QString before returning
        return QString::fromStdString(buffer.str());
    }


    void init() {
        makeCurrent();
        initializeOpenGLFunctions();

        //setMouseTracking(true);// Needed for MouseGrabber.

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

                const float stepSize = 0.01f;
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
                    qreal pitch = camera()->viewDirection().y;

                    if (pitch >= -0.05 && pitch <= 0.05) {
                        qglviewer::Quaternion rotation;
                        rotation.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), stepRotate);
                        camera()->frame()->rotate(rotation);
                    }
                }
                else if (event->key() == Qt::Key_Left) {
                    qreal pitch = camera()->viewDirection().y;

                    if (pitch >= -0.05 && pitch <= 0.05) {
                        qglviewer::Quaternion rotation;
                        rotation.setAxisAngle(qglviewer::Vec(0.0, 1.0, 0.0), stepRotate);
                        camera()->frame()->rotate(rotation);
                    }
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

    /*void mouseDoubleClickEvent( QMouseEvent * e )
    {
        if( (e->modifiers() & Qt::ControlModifier)  &&  (e->button() == Qt::RightButton) )
        {
            pickBackgroundColor();
            return;
        }

        if( (e->modifiers() & Qt::ControlModifier)  &&  (e->button() == Qt::LeftButton) )
        {
            showControls();
            return;
        }

        QGLViewer::mouseDoubleClickEvent( e );
    }*/

    /*void mousePressEvent(QMouseEvent* e ) {
        if (vueActuelle == VuePremierePersonne) {
            lastMousePos = e->pos();
            QGLViewer::mousePressEvent(e);
        }

    }

    void mouseMoveEvent(QMouseEvent* e) {
        if (vueActuelle == VuePremierePersonne) {
            float mouseDeltaX = e->x() - lastMousePos.x();
            float sensitivity = 0.01f;
            float deltaYaw = -mouseDeltaX * sensitivity;

            qglviewer::Quaternion currentOrientation = camera()->frame()->orientation();

            // Limit the change in orientation to yaw (rotation around the vertical axis)
            float yawLimit = 180.0f; // Limit in degrees
            qglviewer::Vec rotationAxis;
            qreal rotationAngle; // Change qreal to the appropriate type used in your application
            currentOrientation.getAxisAngle(rotationAxis, rotationAngle);

            float newYaw = std::clamp(static_cast<float>(rotationAngle) + deltaYaw, -yawLimit, yawLimit);
            deltaYaw = newYaw - static_cast<float>(rotationAngle);

            qglviewer::Quaternion deltaOrientation = qglviewer::Quaternion(rotationAxis, deltaYaw);

            camera()->frame()->setOrientation(currentOrientation * deltaOrientation);
            update();

            lastMousePos = e->pos();
        }

        QGLViewer::mouseMoveEvent(e);
    }*/

    void mousePressEvent(QMouseEvent *e) {
        /*if (vueActuelle == VuePremierePersonne) {
            lastMousePos = e->pos();
                QGLViewer::mousePressEvent(e);
        }*/
    }

    /*void mouseMoveEvent(QMouseEvent *e) {
        double sensibility = 0.05;
        QPoint delta = e->pos() - lastMousePos;
        double angleY = delta.x() * sensibility;

        qglviewer::Quaternion rotation;
        rotation.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), angleY);

        camera()->frame()->rotate(rotation);
        lastMousePos = e->pos();

        update();
    }*/

    /*void mouseMoveEvent(QMouseEvent *e) {
        double sensibility = 0.05;
        QPoint delta = e->pos() - lastMousePos;

        // Rotation autour de l'axe y
        double angleY = delta.x() * sensibility;
        qglviewer::Quaternion rotationY;
        rotationY.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), angleY);
        camera()->frame()->rotate(rotationY);

        // Rotation autour de l'axe x
        double angleX = delta.y() * sensibility;
        qglviewer::Quaternion rotationX;
        rotationX.setAxisAngle(camera()->rightVector(), angleX);

        // Créer une nouvelle orientation en combinant les rotations actuelles avec la rotation autour de l'axe x
        qglviewer::Quaternion newOrientation = rotationX * camera()->frame()->rotation();

        // Vérifier que l'angle X est entre 0 et 90 degrés
        qglviewer::Vec currentUp = newOrientation * camera()->upVector();
        if (currentUp.x > 0.0 && currentUp.x < 1.0) {
            camera()->frame()->setOrientation(newOrientation);
        }

        lastMousePos = e->pos();
        update();
    }*/

    void mouseMoveEvent(QMouseEvent *e) {
        /*if (vueActuelle == VuePremierePersonne) {
            double sensibility = 0.009;
            QPoint delta = e->pos() - lastMousePos;


            qglviewer::Quaternion currentRotation = camera()->frame()->orientation();
            qglviewer::Vec axis;
            double angle;
            currentRotation.getAxisAngle(axis, angle);


            double pitch = axis[0] * angle;
            double yaw = axis[1] * angle;
            double roll = axis[2] * angle;


            double angleY = delta.x() * sensibility;
            qglviewer::Quaternion rotationY;
            rotationY.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), angleY);

            double angleX = delta.y() * sensibility;

            const double maxRotationX = M_PI / 3.0;  // Limite à 60 degrés

            if (angleX > maxRotationX) {
                angleX = maxRotationX;
            }

            qglviewer::Quaternion rotationX;
            rotationX.setAxisAngle(qglviewer::Vec(-1.0, 0.0, 0.0), angleX);

            qglviewer::Quaternion finalRotation = rotationX * rotationY * currentRotation;

            qglviewer::Quaternion rollReset;
            rollReset.setAxisAngle(qglviewer::Vec(0.0, 0.0, 1.0), -roll);
            finalRotation = rollReset * finalRotation;

            finalRotation.normalize();
            camera()->frame()->setOrientation(finalRotation);

            lastMousePos = e->pos();
            update();

        }*/
    }

    void mouseReleaseEvent(QMouseEvent* e) {
        //QGLViewer::mouseReleaseEvent(e);
    }

    void animate() {
        camera()->setPosition(camera()->position() + accumulatedMouseTranslation + accumulatedKeyTranslation);
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
