#include <QString>
#include <string.h>

bool validator(QString *_PrintStr) {
    if((*_PrintStr) == "") {
        return false;
    }
    bool res = true;
    int count_op_br = 0;
    int count_cl_br = 0;

    for (int i = 0; i < _PrintStr->length(); i++) {

        if ((*_PrintStr)[i] == '(') {
            count_op_br++;
        }
        if ((*_PrintStr)[i] == ')') {
            count_cl_br++;
        }
    }
    int count_br = count_op_br - count_cl_br;

    for (; count_br > 0; count_br--) {
        _PrintStr->push_back(")");
    }

    if (count_br < 0) {
        res = false;
    }
    return res;
}
