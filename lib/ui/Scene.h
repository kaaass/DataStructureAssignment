//
// Created by guyis on 2019/5/29.
//

#ifndef DATA_STRCUT_ASSIGN_BASESCENE_H
#define DATA_STRCUT_ASSIGN_BASESCENE_H

#include <vector>
#include <functional>

#include "UI_Utils.h"
#include "Widget.h"

/**
 * 是否更改为享元模式？
 */
class BaseScene implements IWidget {
    std::vector<std::reference_wrapper<IWidget>> widgets;
protected:
    void registerSubWidget(IWidget &widget);

public:
    BaseScene();

    virtual void init();
    void inLoop() override;
    void render() override;

    virtual std::string getTitle();

    /**
     * Triggered before scene created
     */
    virtual void onCreate() {}
    virtual void onInit() {}
    virtual void onLoop() {}
    virtual void onRender() {}
};

#endif //DATA_STRCUT_ASSIGN_BASESCENE_H
