void open_logic(int i, int j) { // ����������� ������� �������� ������
    if (field[i][j].is_open == 1) return;
    field[i][j].is_open = 1;
    if (field[i][j].bombs_around == 0)
        for (int l = -1; l < 2; l++)
            for (int k = -1; k < 2; k++)
                if (((i + l) < FLENGHT && (j + k) < FHIGHT) && ((i + l) >= 0 && (j + k) >= 0))
                    open_logic(i + l, j + k);
}
void null() {
    for (int i = 0; i < FLENGHT; i++) { // ��������� ��� ��������
        for (int j = 0; j < FHIGHT; j++) {
            field[i][j].is_open = 0;
            field[i][j].min = 0;
            field[i][j].bombs_around = 0;
            field[i][j].color = 1;
            field[i][j].flag = 0;
        }
    }
}
void startup(int a, int b) { // ����� ����
    null();
    flag_stay = 0;
    int k = 0;
    srand(time(NULL));
    while (k < mincounter) { // ���������� ����
        int i;
        int j;
        i = 0 + rand() % FLENGHT;
        j = 0 + rand() % FHIGHT;
        if (field[i][j].min != 1 && (i != a || j != b)) {
            field[i][j].min = 1;
            k++;
        }
    }
    for (int i = 0; i < FLENGHT; i++) { // ���������� �������� ���� ������ ������
        for (int j = 0; j < FHIGHT; j++) {
            int bombs = 0;
            for (int l = i - 1; l < i + 2; l++) {
                for (int k = j - 1; k < j + 2; k++) {
                    if ((l >= 0 && k >= 0) && (l < FLENGHT && k < FHIGHT)) {
                        if (field[l][k].min == 1)
                            bombs++;
                    }
                }
            }
            field[i][j].bombs_around = bombs;
            if (field[i][j].min == 1)
                field[i][j].bombs_around = -1;
        }
    }
}
void logic() { // ������
    // ���������������
    int width, height;
    glfwGetWindowSize(window, &width, &height); // ��������� �������� ����
    float aspect = (float)width / height; // ����������� ������ � ������
    glViewport(0, 0, height, height); // ��������� �������� ������������ ������� ����
    glfwGetCursorPos(window, &xpos, &ypos); // ������ ������� 
    glfwSetMouseButtonCallback(window, mouse_button_callback); // ������ ������� �� ���� 
    glfwSetKeyCallback(window, key_callback); // ������ ������� �� �������
    // ���������������
    xpos /= (width / aspect);// ���������� � ������������� ����������
    ypos /= height; // ���������� � ������������� ����������
    for (int i = 0; i < FLENGHT; i++) { // �������� �� ��������� ������� ������������ ��������� ��� ���� � ������� ������ ����
        for (int j = 0; j < FHIGHT; j++) {
            if ((xpos > i * 0.05 + 0.0f + (sdwg/2) && xpos <  i * 0.05 + 0.04f + (sdwg / 2)) && (ypos >  j * 0.05 + 0.0f + (sdwg / 2) && ypos < j * 0.05 + 0.04f + (sdwg / 2))) {
                field[i][j].color = 1.5; // ��������� ����� ��� ��������� ���� �� �������
                if (m_press == 1) {
                    if (field[i][j].is_open == 0) // �������� ������
                        PlaySound(L"source/bull.wav", NULL, SND_ASYNC);
                        open_logic(i, j);
                    if (field[i][j].min == 1)
                        gameover = 1;
                    if (gamemode != 0 && m_press_first == 0 && gamemode != 4) {
                        m_press_first = 1;
                        startup(i,j,mincounter);
                        open_logic(i, j);
                    }
                }
                if (m_press == 2) { // ������ ����
                    if (field[i][j].flag == 0) {
                        field[i][j].flag = 1;
                        flag_stay++;
                    }
                    else {
                        field[i][j].flag = 0;
                        flag_stay--;
                    }
                }
            }
            else
                field[i][j].color = 1;
        }
    }
    if (flag_stay == mincounter && m_press_first > 0) { // �������� �� ������
        int k = 0;
        for (int i = 0; i < FLENGHT; i++) {
            for (int j = 0; j < FHIGHT; j++) {
                if (field[i][j].min == field[i][j].flag)
                    k++;
            }
        }
        if (k == FLENGHT*FHIGHT)
            gameover = 2;
    }
    m_press = 0; // ����� ������� ����
}
void save() {
    FILE* fp = fopen("save.bin", "wb");
    fwrite(&FLENGHT, sizeof(int), 1, fp);
    fwrite(&FHIGHT, sizeof(int), 1, fp);
    fwrite(&mincounter, sizeof(int), 1, fp);
    fwrite(&sdwg, sizeof(float), 1, fp);
    fwrite(&flag_stay, sizeof(int), 1, fp);
    for (int i = 0; i < FLENGHT; i++)
        for (int j = 0; j < FHIGHT; j++) {
            fwrite(&field[i][j].is_open, sizeof(int), 1, fp);
            fwrite(&field[i][j].min, sizeof(int), 1, fp);
            fwrite(&field[i][j].flag, sizeof(int), 1, fp);
            fwrite(&field[i][j].bombs_around, sizeof(int), 1, fp);
        }
    fclose(fp);
    exit(0);
}
void saveload() { // �������� ��������
    FILE* fp = fopen("save.bin", "rb"); // �������� ����� � �����
    fread(&FLENGHT, sizeof(int), 1, fp);
    fread(&FHIGHT, sizeof(int), 1, fp);
    fread(&mincounter, sizeof(int), 1, fp);
    fread(&sdwg, sizeof(float), 1, fp);
    fread(&flag_stay, sizeof(int), 1, fp);
    for (int i = 0; i < FLENGHT; i++)
        for (int j = 0; j < FHIGHT; j++) {
            fread(&field[i][j].is_open, sizeof(int), 1, fp);
            fread(&field[i][j].min, sizeof(int), 1, fp);
            fread(&field[i][j].flag, sizeof(int), 1, fp);
            fread(&field[i][j].bombs_around, sizeof(int), 1, fp);
        }
    fclose(fp); // �������� �����
}
void logic_m() { // ������ ����
    int width, height;
    glfwGetCursorPos(window, &xpos, &ypos); // ������ ������� 
    glfwSetMouseButtonCallback(window, mouse_button_callback); // ������ ������� �� ���� 
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, height, height);
    float aspect = (float)width / height;
    xpos /= (width / aspect); // ���������� � ������������� ����������
    ypos /= height; // ���������� � ������������� ����������
    // ������ �������� �� ������� ������ �� ������ 
    if (xpos > 0.1 && xpos < 0.45 && ypos > 0.1 && ypos < 0.45) { // �������� ��������� ����
        if (m_press == 1) {
            gamemode = 1; // ��������� ������ ����
        }
        colorchange[0] = 1.5;// ��������� ����� ������
    }
    else if (xpos > 0.5 && xpos < 0.85 && ypos > 0.1 && ypos < 0.45) {
        if (m_press == 1) {
            gamemode = 2;
        }
        colorchange[1] = 1.5;
    }
    else if (xpos > 0.1 && xpos < 0.45 && ypos > 0.5 && ypos < 0.85) {
        if (m_press == 1) {
            gamemode = 3;
        }
        colorchange[2] = 1.5;
    }
    else if (xpos > 0.5 && xpos < 0.85 && ypos > 0.5 && ypos < 0.85) {
        if (m_press == 1) {
            gamemode = 4;
            saveload();
        }
        colorchange[3] = 1.5;
    }
    else { // ����� ��������� �����
        colorchange[0] = 1;
        colorchange[1] = 1;
        colorchange[2] = 1;
        colorchange[3] = 1;
    }
    m_press = 0;
}
void helpmin() {
    for (int i = 0; i < FLENGHT; i++) {
        for (int j = 0; j < FHIGHT; j++) {
            if (field[i][j].is_open == 1) {
                int close = 0;
                for (int l = i - 1; l < i + 2; l++) {
                    for (int k = j - 1; k < j + 2; k++) {
                        if ((l >= 0 && k >= 0) && (l < FLENGHT && k < FHIGHT)) {
                            if (field[l][k].is_open == 0)
                                close++;
                        }
                    }
                }
                field[i][j].close = close;
            }
        }
    }
    for (int i = 0; i < FLENGHT; i++) {
        for (int j = 0; j < FHIGHT; j++) {
            if (field[i][j].close == field[i][j].bombs_around && field[i][j].is_open == 1 && field[i][j].bombs_around != 0) {
                for (int l = i - 1; l < i + 2; l++) {
                    for (int k = j - 1; k < j + 2; k++) {
                        if ((l >= 0 && k >= 0) && (l < FLENGHT && k < FHIGHT)) {
                            field[l][k].color = 1.5;
                        }
                    }
                }
            }
        }
    }
}