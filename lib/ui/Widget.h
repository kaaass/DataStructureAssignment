//
// Created by guyis on 2019/5/29.
//

#ifndef DATA_STRCUT_ASSIGN_WIDGET_H
#define DATA_STRCUT_ASSIGN_WIDGET_H

class IWidget {
public:
    /**
     * render trigger
     */
    virtual void render() = 0;

    /**
     * inLoop trigger
     */
    virtual void inLoop() = 0;
};

#endif //DATA_STRCUT_ASSIGN_WIDGET_H
