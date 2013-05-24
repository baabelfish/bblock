#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <security/pam_appl.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

void init() {
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    // raw();
    nodelay(stdscr, true);
    wtimeout(stdscr, 200);
    keypad(stdscr, true);
    use_default_colors();
    start_color();
    init_pair(225, -1, -1);
    init_pair(1, 1, 1);
    init_pair(2, 10, 10);
    init_pair(3, 3, 3);
    init_pair(4, 4, 4);
    init_pair(5, 5, 5);
    curs_set(0);
}

struct pam_response *reply;

int function_conversation(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr) {
    *resp = reply;
    return PAM_SUCCESS;
}

bool authenticate(const std::string& password) {
    int retval;
    const struct pam_conv local_conversation = { function_conversation, NULL };
    pam_handle_t *handle = NULL;

    char *p = getenv("USER");
    if (p == NULL) {
        return false;
    }

    if (pam_start("common-auth", p, &local_conversation, &handle) != PAM_SUCCESS) {
        return false;
    }

    char* cpasswd = new char[password.length() + 1];
    strcpy(cpasswd, password.c_str());
    reply = (struct pam_response *)malloc(sizeof(struct pam_response));
    reply[0].resp = cpasswd;
    reply[0].resp_retcode = 0;

    if (pam_authenticate(handle, 0) != PAM_SUCCESS) {
        pam_end(handle, retval);
        return false;
    }

    pam_end(handle, retval);
    return true;
}

void drawLine(int color, int delay = 0) {
    int size_x = 0;
    int size_y = 0;
    getmaxyx(stdscr, size_y, size_x);
    attron(COLOR_PAIR(color));

    move(size_y - 1, 0);
    for (auto x = 0; x < size_x; ++x) {
        mvaddch(size_y - 1, x, ' ');
    }

    refresh();
    sleep(delay);
}

int main(int argc, char* argv[]) {
    init();
    std::string pass;

    while (true) {
        int key = getch();
        drawLine(225);
        
        if (key != -1 && key != 0) {
            std::stringstream vittu;
            std::string ckey;
            vittu << (char)key;
            vittu >> ckey;

            drawLine(3);
            
            if (key == 127 && pass.size() > 0) {
                pass = pass.substr(0, pass.size() - 1);
            }
            else if (key == '\n' || key == '\r') {
                drawLine(4);
                if (authenticate(pass)) {
                    drawLine(2, 2);
                    attroff(A_BLINK);
                    attroff(A_UNDERLINE);
                    attroff(A_BOLD);
                    endwin();
                    return 0;
                }
                drawLine(1, 2);
                pass.clear();
            }
            else {
                pass += ckey;
            }
        }
    }
    endwin();
    return 1;
}
