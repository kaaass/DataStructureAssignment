//
// Created by guyis on 2019/5/29.
//

#ifndef DATA_STRCUT_ASSIGN_WIDGET_H
#define DATA_STRCUT_ASSIGN_WIDGET_H

class IWidget {

    bool enabled;
public:
    IWidget() : enabled(false) {}

    /**
     * render trigger
     */
    virtual void render() = 0;

    /**
     * inLoop trigger
     */
    virtual void inLoop() = 0;

    virtual ~IWidget() = default;

    void setEnabled(bool enabled) {
        IWidget::enabled = enabled;
    }

    bool isEnabled() const {
        return enabled;
    }
};

#endif //DATA_STRCUT_ASSIGN_WIDGET_H
