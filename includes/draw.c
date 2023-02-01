
void flag(int x, int y) {
    glBegin(GL_TRIANGLES);
    glColor3f(255, 0, 0);
    glVertex2f(sdwg + x * 0.1 + 0.01, -sdwg + y * -0.1 - 0.02);
    glVertex2f(sdwg + x * 0.1 + 0.05, -sdwg + y * -0.1 - 0.008);
    glVertex2f(sdwg + x * 0.1 + 0.05, -sdwg + y * -0.1 - 0.04);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(sdwg + x * 0.1 + 0.05, -sdwg + y * -0.1 - 0.008);
    glVertex2f(sdwg + x * 0.1 + 0.05, -sdwg + y * -0.1 - 0.08);
    glEnd();
}
void Line(float x1, float y1, float x2, float y2) {
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
}
void ShowCount(int a, float x, float y) {
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    if ((a != 1) && (a != 4))
        Line( x + 0.02, y  - 0.026, x + 0.046,y - 0.026);
    if ((a != 0) && (a != 1) && (a != 7))
        Line(x+ 0.02, y - 0.04, x + 0.046,  y - 0.04);
    if ((a != 1) && (a != 4) && (a != 7))
        Line(x  + 0.02,  y - 0.06,  x  + 0.046,  y - 0.06);
    if ((a != 5) && (a != 6))
        Line( x  + 0.046,  y  - 0.04, x + 0.046, y - 0.026);
    if (a != 2)
        Line(x + 0.046, y  - 0.04,  x + 0.046,  y - 0.06);
    if ((a != 1) && (a != 2) && (a != 3) && (a != 7))
        Line( x + 0.02, y  - 0.04, x + 0.02 , y  - 0.026);
    if ((a == 0) || (a == 2) || (a == 6) || (a == 8))
        Line( x + 0.02 , y  - 0.04, x  + 0.02,  y - 0.06);
    glEnd();
}
void squaredraw(float x1, float y1, float x2, float y2, float R, float G, float B, float color) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(R * color, G * color, B * color);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
}
void fielddraw() { // отрисовка поля
    for (int i = 0; i < FLENGHT; i++) {
        for (int j = 0; j < FHIGHT; j++) {
            if (field[i][j].min == 1)
                squaredraw(sdwg + i * 0.1 +0.01, -sdwg - j *0.1 -0.01, sdwg + i * 0.1 +0.06,-sdwg - j*0.1-0.06,255,0,0,1);
            if (field[i][j].is_open == 1 && field[i][j].bombs_around > 0)
                ShowCount(field[i][j].bombs_around, sdwg + i * 0.1, -sdwg + j * -0.1);
            if (field[i][j].is_open == 0) 
                squaredraw(sdwg + i*0.1 + 0.00, -sdwg - j*0.1 + 0.00, sdwg + i * 0.1 + 0.08, -sdwg - j * 0.1 - 0.08,0.06,0.6,0.00,field[i][j].color);
            if (field[i][j].flag == 1 && field[i][j].is_open == 0)
                flag(i, j);
        }
    }

}
void counter(int count, int count2, int gamemode) {

    if (count >= 100)
    ShowCount(count / 100,1.65,0.005);
    if (count >= 10)
    ShowCount(count / 10, 1.70,0.005);
    ShowCount(count - ((count / 10) * 10), 1.74,0.005);
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    Line(1.82, -0.012, 1.8, -0.065);
    glEnd();
    ShowCount(count2 / 10, 1.81,0.005);
    ShowCount(count2 - ((count2 / 10) * 10), 1.85,0.005);
}
void m_draw(float color1, float color2, float color3, float color4) {
    squaredraw(0.2,-0.2,0.9,-0.9,0.06,0.6,0.0,color1);
    squaredraw(1.0,-0.2,1.7,-0.9,0.06,0.6,0.0,color2);
    squaredraw(0.2,-1.0,0.9,-1.7,0.06,0.6,0.0,color3);
    squaredraw(1.0, -1.0, 1.7, -1.7, 0.06, 0.6, 0.0, color4);
}
void fortex(char* texname, int a) {
    int width, height, cnt;
    unsigned char* data = stbi_load(texname, &width, &height, &cnt, 0);
    glGenTextures(1, &texturs[a]);
    glBindTexture(GL_TEXTURE_2D, texturs[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
void text(char* texname) {
    if (texname == "source/03.png") {
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturs[0]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);         glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);         glVertex2f(2.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);         glVertex2f(2.0f, -2.0f);
        glTexCoord2f(0.0f, 1.0f);         glVertex2f(0.0f, -2.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
    if (texname == "source/15x15.png") {
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturs[1]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);         glVertex2f(0.2f, -0.2f);
        glTexCoord2f(1.0f, 0.0f);         glVertex2f(0.8f, -0.2f);
        glTexCoord2f(1.0f, 1.0f);         glVertex2f(0.8f, -0.8f);
        glTexCoord2f(0.0f, 1.0f);         glVertex2f(0.2f, -0.8f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
    if (texname == "source/10x10.png") {
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturs[2]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);         glVertex2f(1.0f, -0.2f);
        glTexCoord2f(1.0f, 0.0f);         glVertex2f(1.6f, -0.2f);
        glTexCoord2f(1.0f, 1.0f);         glVertex2f(1.6f, -0.8f);
        glTexCoord2f(0.0f, 1.0f);         glVertex2f(1.0f, -0.8f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
    if (texname == "source/12x12.png") {
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturs[3]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);         glVertex2f(0.2f, -1.0f);
        glTexCoord2f(1.0f, 0.0f);         glVertex2f(0.8f, -1.0f);
        glTexCoord2f(1.0f, 1.0f);         glVertex2f(0.8f, -1.6f);
        glTexCoord2f(0.0f, 1.0f);         glVertex2f(0.2f, -1.6f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
    if (texname == "source/lose.png") {
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturs[4]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);         glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);         glVertex2f(2.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);         glVertex2f(2.0f, -2.0f);
        glTexCoord2f(0.0f, 1.0f);         glVertex2f(0.0f, -2.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
}
