//
// Created by guyis on 2019/5/31.
//

#ifndef DATA_STRCUT_ASSIGN_LABEL_H
#define DATA_STRCUT_ASSIGN_LABEL_H

#include <string>
#include "../UI_Utils.h"
#include "../Widget.h"

class Label implements IWidget {
    int x;
    int y;
    int w;
    bool mid;
    std::string content;

public:
    Label(int x, int y, int w, bool mid);

    void render() override;

    void inLoop() override;

    void setText(const std::string &str);

    std::string getText();

    ~Label() = default;
};

#endif //DATA_STRCUT_ASSIGN_LABEL_H
