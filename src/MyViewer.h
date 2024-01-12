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
#include <QImage>
#include <QQuaternion>
#include <QRandomGenerator>

#include <limits>
#include <QDebug>

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

    GLuint cubemapTexture; //Cube

    GLuint skyboxShader;
    GLuint skyboxVAO, skyboxVBO;

    GLuint vertexbuffer, indexbuffer, normalBuffer, textureCoordBuffer;
    GLuint textureEauID,textureHerbeID, textureRocheID, textureNeigeID, textureHeightmapID;

    qglviewer::Camera camVuePremierePersonne;

public :
    TerrainMesh terrainMesh;
    float randPosX, randPosZ;

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

    void loadSkybox() {
        // Load the skybox shaders
        QString skyboxVertexShaderSource = readShaderFile("src/skybox_vshader.glsl");
        QString skyboxFragmentShaderSource = readShaderFile("src/skybox_fshader.glsl");

        skyboxShader = createShaderProgram(skyboxVertexShaderSource.toUtf8().constData(), skyboxFragmentShaderSource.toUtf8().constData());

        // Set up skybox vertices
        GLfloat skyboxVertices[] = {
            // Positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };


        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);

        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void drawSkybox() {
        glUseProgram(skyboxShader);
        glUniform1i(glGetUniformLocation(skyboxShader, "cubemapTexture"), 5);

        glDisable(GL_DEPTH_TEST);

        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "modelS"), 1, GL_FALSE, modelMatrix.data());


        GLfloat viewMatrix[16];
        camera()->getModelViewMatrix(viewMatrix);

        // Supprimer les composantes de translation de la viewMatrix
        viewMatrix[12] = 0.0f;
        viewMatrix[13] = 0.0f;
        viewMatrix[14] = 0.0f;

        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "viewS"), 1, GL_FALSE, viewMatrix);


        GLfloat projectionMatrix[16];
        camera()->getProjectionMatrix(projectionMatrix);
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projectionS"), 1, GL_FALSE, projectionMatrix);

        glBindVertexArray(skyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glEnable(GL_DEPTH_TEST);

        glUseProgram(0);
    }


    void loadCubemap() {
        glGenTextures(1, &cubemapTexture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

        const char* faces[6] = {
            "./images/right.jpg",
            "./images/left.jpg",
            "./images/top.jpg",
            "./images/bottom.jpg",
            "./images/front.jpg",
            "./images/back.jpg"
        };

        for (unsigned int i = 0; i < 6; i++) {
            QImage image(faces[i]);

            if (!image.isNull()) {
                image = image.convertToFormat(QImage::Format_RGB888);

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
            } else {
                qDebug() << "Cubemap texture failed to load at path: " << faces[i];
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
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

    GLuint loadTextureHeightmap(QImage image)
    {
        image = image.convertToFormat(QImage::Format_RGBA8888);

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return textureID;
    }

    void loadTextures() {
        textureEauID = loadTexture("./images/textureEau.jpg");
        textureHerbeID = loadTexture("./images/textureHerbe.jpg");
        textureRocheID = loadTexture("./images/textureRoche.jpg");
        textureNeigeID = loadTexture("./images/textureNeige.jpg");
        //textureHeightmapID = loadTexture("perlinNoise.png");
        textureHeightmapID = loadTextureHeightmap(terrainMesh.perlinNoise->ImgPerlin);
    }

    void drawBuffers() {
        //GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.vertex_buffer.size() * sizeof(QVector3D), &terrainMesh.vertex_buffer[0], GL_STATIC_DRAW);

        //GLuint indexbuffer;
        glGenBuffers(1, &indexbuffer);
        //glBindBuffer(GL_ARRAY_BUFFER, indexbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrainMesh.index_buffer.size() * sizeof(short), &terrainMesh.index_buffer[0], GL_STATIC_DRAW);

        //GLuint normalBuffer;
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, terrainMesh.normal_buffer.size() * sizeof(float), &terrainMesh.normal_buffer[0], GL_STATIC_DRAW);

        //Texture
        //GLuint textureCoordBuffer;
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

        //Texture
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, textureCoordBuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, /*0*/2 * sizeof(float), (void*)0);

        QString vertexShaderSource = readShaderFile("src/vshader.glsl");
        QString fragmentShaderSource = readShaderFile("src/fshader.glsl");

        shaderProgram = createShaderProgram(vertexShaderSource.toUtf8().constData(), fragmentShaderSource.toUtf8().constData());

        // Charger les textures
        /*textureEauID = loadTexture("./images/textureEau.jpg");
        textureHerbeID = loadTexture("./images/textureHerbe.jpg");
        textureRocheID = loadTexture("./images/textureRoche.jpg");
        textureNeigeID = loadTexture("./images/textureNeige.jpg");
        //textureHeightmapID = loadTexture("perlinNoise.png");
        textureHeightmapID = loadTextureHeightmap(terrainMesh.perlinNoise->ImgPerlin);*/

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

        glUniform1i(glGetUniformLocation(shaderProgram, "textureEau"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureHerbe"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureRoche"), 2);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureNeige"), 3);
        glUniform1i(glGetUniformLocation(shaderProgram, "textureHeightmap"), 4);

        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glUniform1i(glGetUniformLocation(shaderProgram, "cubemapTexture"), 5);

    }

    bool isActualTextureWater(qglviewer::Vec cameraPosition) {
        GLfloat centerY = cameraPosition.y - 0.2f;

        if (centerY <= 0.0f && centerY < 0.2) {
            return true;
        }

        return false;
    }


    void drawTerrainView() {
        drawBuffers();
    }

    GLfloat getThisPositionHeight(float camPosX, float camPosZ) {
        float stepX = static_cast<float>(terrainMesh.sizeX) / static_cast<float>(terrainMesh.resolution);
        float stepZ = static_cast<float>(terrainMesh.sizeZ) / static_cast<float>(terrainMesh.resolution);

        int i = static_cast<int>(camPosX / stepX);
        int j = static_cast<int>(camPosZ / stepZ);

        float perlin = terrainMesh.perlinNoise->getPerlinAt(i, j, terrainMesh.resolution);
        GLfloat centerY;
        terrainMesh.getHeightAtPerlinPx(centerY, perlin);

        return centerY;
    }

    /*void initPremierePersonneCamera() {
        float centerX = terrainMesh.sizeX / 2.0f;
        float centerZ = terrainMesh.sizeZ / 2.0f;

        QMatrix4x4 customModelViewMatrix;
        customModelViewMatrix.setToIdentity();

        modelMatrix.setToIdentity();
        applyRotation(modelMatrix);

        camVuePremierePersonne.loadModelViewMatrix(customModelViewMatrix.data());

        GLfloat centerY = getThisPositionHeight(centerX, centerZ) + 0.2f;

        qglviewer::Vec cameraPosition(centerX, centerY, centerZ);
        camVuePremierePersonne.setPosition(cameraPosition);
    }*/

    qglviewer::Vec spawnAt() {
        qglviewer::Vec cameraPosition;

        QMatrix4x4 customModelViewMatrix;
        customModelViewMatrix.setToIdentity();

        modelMatrix.setToIdentity();
        applyRotation(modelMatrix);

        camera()->loadModelViewMatrix(customModelViewMatrix.data());

        GLfloat y = getThisPositionHeight(randPosX, randPosZ) + 0.2f;

        cameraPosition.x = randPosX;
        cameraPosition.y = y;
        cameraPosition.z = randPosZ;

        return cameraPosition;
    }

    void drawPremierePersonneView() {
        qglviewer::Vec cameraPosition = spawnAt();

        camera()->setSceneRadius(terrainMesh.sizeX * 2.0);
        camera()->setPosition(cameraPosition);

        drawBuffers();
        animate();
    }


    void setCameraPositionWithPerlinHeight() {
        qglviewer::Vec cameraPosition = camera()->position();
        GLfloat centerY = getThisPositionHeight(cameraPosition.x, cameraPosition.z);

        cameraPosition.y = centerY+ 0.2f;
        camera()->setPosition(cameraPosition);
    }

    void draw() {
        //skybox
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawSkybox();

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
        //

        glShadeModel(GL_SMOOTH);
        glFrontFace(GL_CCW); // CCW ou CW

        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CLIP_PLANE0);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_COLOR_MATERIAL);

        loadCubemap();
        loadSkybox();

        //

        point3d bbmin(0.0, 0.0, 0.0) , BBmax(1, 1, 1);
        adjustCamera(bbmin, BBmax);

        modelMatrix = QMatrix4x4();

        //initPremierePersonneCamera();

        loadTextures();

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
            static int nbMvt = 0;
            if (nbMvt == 0 && event->key() == Qt::Key_Left) {
                rotateObjectLeft();
            }
            else if (nbMvt == 0 && event->key() == Qt::Key_Right) {
                rotateObjectRight();
            }
            else if (nbMvt < 20 && event->key() == Qt::Key_Up) {
                rotateObjectUp();
                nbMvt++;
                //qDebug() << nbMvt;
            }
            else if (nbMvt > 0 && event->key() == Qt::Key_Down) {
                rotateObjectDown();
                nbMvt--;
            }
        }
        else if (vueActuelle == VuePremierePersonne) {
            static int nbMvtFPS = 0;

            const float stepSize = 1.f/terrainMesh.resolution;
            const float stepRotate = 0.05f;

            if (event->key() == Qt::Key_Q) {
                accumulatedKeyTranslation += camera()->frame()->inverseTransformOf(qglviewer::Vec(-stepSize, 0, 0));
            } else if (event->key() == Qt::Key_D) {
                accumulatedKeyTranslation += camera()->frame()->inverseTransformOf(qglviewer::Vec(+stepSize, 0, 0));
            } else if (event->key() == Qt::Key_Z) {
                accumulatedKeyTranslation += camera()->frame()->inverseTransformOf(qglviewer::Vec(0, 0, -stepSize));
            } else if (event->key() == Qt::Key_S) {
                accumulatedKeyTranslation += camera()->frame()->inverseTransformOf(qglviewer::Vec(0, 0, stepSize));
            }
            if (event->key() == Qt::Key_Escape) {
                vueActuelle = VueTerrain;
                openCameraFromFile("initCam.txt");
                terrainMesh.sizeX = 1.0;
                terrainMesh.sizeY = 1.0;
                terrainMesh.sizeZ = 1.0;
                terrainMesh.generateMesh();

                update();
                point3d bbmin(0.0, 0.0, 0.0) , BBmax(1, 1, 1);
                adjustCamera(bbmin, BBmax);

            }

            else if (/*nbMvtFPS < 20 &&*/ event->key() == Qt::Key_Up) {
                qreal pitch = camera()->viewDirection().y;

                if (pitch <= 0.4) {
                    qglviewer::Quaternion rotation;
                    rotation.setAxisAngle(qglviewer::Vec(1.0, 0.0, 0.0), stepRotate);
                    camera()->frame()->rotate(rotation);
                    nbMvtFPS++;
                }
            }
            else if (/*nbMvtFPS > 0 &&*/ event->key() == Qt::Key_Down) {
                qreal pitch = camera()->viewDirection().y;

                if (pitch >= -0.7) {
                    qglviewer::Quaternion rotation;
                    rotation.setAxisAngle(qglviewer::Vec(-1.0, 0.0, 0.0), stepRotate);
                    camera()->frame()->rotate(rotation);
                    nbMvtFPS--;
                }
            }
            else if (nbMvtFPS == 0 && event->key() == Qt::Key_Right) {
                qglviewer::Quaternion rotation;
                rotation.setAxisAngle(qglviewer::Vec(0.0, -1.0, 0.0), stepRotate);
                camera()->frame()->rotate(rotation);
            }
            else if (nbMvtFPS == 0 && event->key() == Qt::Key_Left) {
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

    void wheelEvent(QWheelEvent *e) {
        static int nbZoom = 0;

        if (vueActuelle == VueTerrain) {
            float delta = e->delta();

            qglviewer::Vec cameraPosition = camera()->position();
            qglviewer::Vec cameraViewDir = camera()->viewDirection();
            float zoomFactor = 0.2;

            if (delta > 0){
                camera()->setPosition(cameraPosition + zoomFactor * cameraViewDir); // Zoom in
                nbZoom++;
            } else{
                if(nbZoom > -1){
                    camera()->setPosition(cameraPosition - zoomFactor * cameraViewDir); // Zoom out
                    nbZoom--;
                }

            }
            qDebug() << nbZoom;



            update();
        }


    }

    void mousePressEvent(QMouseEvent *event) {}

    void mouseMoveEvent(QMouseEvent *event) {}

    void mouseReleaseEvent(QMouseEvent* event) {}

    void animate() {
        qglviewer::Vec cameraPosition = camera()->position() + accumulatedKeyTranslation;

        cameraPosition.x = qBound(0.2f, (float)cameraPosition.x, (float)terrainMesh.sizeX-0.2f);
        cameraPosition.z = qBound(0.2f, (float)cameraPosition.z, (float)terrainMesh.sizeZ-0.2f);

        camera()->setPosition(cameraPosition);
        setCameraPositionWithPerlinHeight();
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
