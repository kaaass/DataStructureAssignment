//
// Created by guyis on 2019/6/12.
//

#ifndef DATA_STRCUT_ASSIGN_STATSCENE_H
#define DATA_STRCUT_ASSIGN_STATSCENE_H

#include <ui/Scene.h>
#include <ui/widget/Label.h>
#include <ui/widget/Table.h>

class StatScene : virtual public BaseScene {
    Label *title;
    Table *statTable;
    FILE *file;

public:
    StatScene(FILE *file) : BaseScene(), file(file) {}

    std::string getTitle() override;

    void onCreate() override;

    void onInit() override;

    void onLoop() override;
};

#endif //DATA_STRCUT_ASSIGN_STATSCENE_H
