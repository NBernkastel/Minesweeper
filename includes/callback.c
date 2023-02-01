
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) // проверка на нажатие мыши
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        m_press = 1;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        m_press = 2;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (gamemode == 4) {
            saveload();
            gameover = 0;
        }
        else
        refresh = 1;
    }
    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        helpmin();
        whenhelp = 1;
    }
    if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
        whenhelp = 0;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS && gameover == 0) {
        save();
    }
}
