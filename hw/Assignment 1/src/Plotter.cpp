#include "Plotter.h"
#include <strlib.h>
using namespace std;

PenStyle pen;

typedef struct _status{
    double x;
    double y;
    bool down;
} Status;

Status status;

void runPlotterScript(istream& input) {
    pen.width = 1;
    pen.color = "#000000";
    status.x = 0;
    status.y = 0;
    status.down = false;

    stringstream ss;
    ss << input.rdbuf();
    auto scripts = stringSplit(toLowerCase(ss.str()), '\n');
    for(auto s: scripts){
        auto words = stringSplit(s, ' ');
        if(words[0] == "pendown"){
            status.down = true;
        }else if(words[0] == "penup"){
            status.down = false;
        }else if(words[0] == "moveabs"){
            double target_x = stod(words[1]), target_y = stod(words[2]);
            if(status.down){
                drawLine(status.x, status.y, target_x, target_y, pen);
            }
            status.x = target_x;
            status.y = target_y;
        }else if(words[0] == "moverel"){
            double dx = stod(words[1]), dy = stod(words[2]);
            double target_x = status.x + dx, target_y = status.y + dy;
            if(status.down){
                drawLine(status.x, status.y, target_x, target_y, pen);
            }
            status.x = target_x;
            status.y = target_y;

        }else if(words[0] == "pencolor"){
            pen.color = words[1];
        }else if(words[0] == "penwidth"){
            pen.width = stoi(words[1]);
        }

    }
}
