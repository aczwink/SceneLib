/*
 * Copyright (c) 2017 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of SceneConverter.
 *
 * SceneConverter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SceneConverter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SceneConverter.  If not, see <http://www.gnu.org/licenses/>.
 */
//Class header
#include "MainWindow.hpp"

//Local instances
class SceneTreeController : public ATreeController
{
private:
    //Members
    CString categories[3];
public:
    //Constructor
    SceneTreeController()
    {
        categories[0] = "Meshes";
        categories[1] = "Materials";
        categories[2] = "Textures";
    }

    //Methods
    void *GetChild(void *pNode, uint32 child) const override
    {
        if(pNode == nullptr)
            return (void *)&this->categories[child];

        return nullptr;
    }

    uint32 GetNumberOfChildren(void *pNode) const override
    {
        if(pNode == nullptr)
            return sizeof(categories)/ sizeof(categories[0]);

        return 0;
    }

    CString GetText(void *pNode) const override
    {
        for(uint32 i = 0; i < sizeof(categories)/ sizeof(categories[0]); i++)
            if(&this->categories[i] == pNode)
                return this->categories[i];

        return "";
    }
};

static SceneTreeController g_sceneTreeController;

//Constructor
MainWindow::MainWindow()
{
    this->SetupActions();
    this->SetupChildren();
    this->SetupMenu();
}

//Private methods
void MainWindow::SetupActions()
{
    this->importAction.text = "Import";
    this->importAction.triggeredEvent = [this]()
    {
        CLinkedList<CTuple<CString, CString>> filters;

        stdOut << CommonDialogs::OpenFile(*this, "Import file...", filters) << endl;
    };
}

void MainWindow::SetupChildren()
{
    this->pSceneTree = new CTreeView(this);
    this->pSceneTree->SetController(g_sceneTreeController);
}

void MainWindow::SetupMenu()
{
    CMenu *pMenu;

    //File
    pMenu = new CMenu("File");
    this->GetMenuBar()->AppendMenu(pMenu);

    pMenu->AppendItem(this->importAction);
}