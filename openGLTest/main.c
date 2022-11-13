//
//  main.c
//  openGLTest
//
//  Created by 小田竜太郎 on 2020/01/14.
//  Copyright © 2020 小田竜太郎. All rights reserved.
//k

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

const GLfloat lightPosition1[4] = {0.0f, 3.0f, 5.0f, 1.0f};
const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};//緑色
const GLfloat lightPosition2[4] = { 5.0f, 3.0f, 0.0f, 1.0f};
const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};//赤色

const GLfloat teapotAmbient[4] = {0.3f, 0.5f, 0.0f, 1.0f};
const GLfloat teapotDiffuse[4] = {1.0f, 1.0f, 0.3f, 1.0f};
const GLfloat teapotSpecular[4] = {0.3f, 0.5f, 0.0f, 1.0f};
const GLfloat teapotShiniess[4] = {20.0f};

void setup(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClearColor(float r, float g, float b, float a);
    //色えをRGBA（Aは透明度）で指定
    glEnable(GL_DEPTH_TEST);
    //隠面消去を有効にする
    //glEnable() 関数はその機能を有効にし、glDisable() 関数は無効にする
    glEnable(GL_LIGHTING);
    // 陰影付けを有効にする
    glEnable(GL_LIGHT0);
    //0番目の光源をオン
    glEnable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
    //光源の位置設定　照明
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);//拡散光
    glLightfv(GL_LIGHT0, GL_SPECULAR, red);//鏡面光
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient);//環境光
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShiniess);//鏡面光ハイライト
}

void draw(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //画面全体を塗りつぶす　バッファの初期化
    glutSolidTeapot(0.5);
    glFlush();
}

void resize(int width, int height){
    glViewport(0, 0, width, height);//ビューポートの設定　ウィンドウ全体
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// 射影行列を操作する
    gluPerspective(45.0, (double)width/height, 0.1, 100.0);// 行列を初期化
    //視野領域の決定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.5, 2.1, 2.0, //視点位置
              0.0, 0.0, 0.0,  //注視点
              0.0, 4.0, 0.0); //姿勢(どっちが上か)
    //視点位置の設定
}

void display(viod){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutWireTeapot(0.5);
    glFlush();
    //シーンの描画
}

int main(int argc, char * argv[]){
    glutInit(&argc, argv);//GLUTを初期化
    glutInitWindowSize(600, 600);//画面サイズを指定する
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);// 表示モード設定
    glutCreateWindow("Wire_teapot");// ウィンドウの名前
    glutReshapeFunc(resize);// reshapeが必要なときに呼ばれる
    glutDisplayFunc(draw);// 描画処理が必要なときに呼ばれる
    setup();
    glutMainLoop();// 毎フレームのLoop
    return 0;
}
