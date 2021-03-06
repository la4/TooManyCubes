#include <QToolBar>
#include <QGridLayout>

#include "mainwindow.h"
#include "qt3dwindow.h"
#include "scene.h"
#include "player.h"
#include "quickactionspanel.h"
#include "toolspanel.h"
#include "colorselectorpanel.h"

namespace TMC {

MainWindow::MainWindow(Scene *scene, QWidget *parent)
    : QMainWindow(parent)
    , mScene(scene) {
    auto *qt3DWindow = new Qt3DExtras::Qt3DWindow();
    qt3DWindow->setRootEntity(scene->getRootEntity());

    // TODO: not a good place for Player creation, move when refactoring
    Player *player = new Player(scene, qt3DWindow->camera()); // tied to scene

    // UI
    auto centralWidget = new QWidget();
    auto gridLayout = new QGridLayout();

    gridLayout->setColumnStretch(0, 0);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setRowStretch(0, 0);
    gridLayout->setRowStretch(1, 1);
    gridLayout->setRowStretch(2, 0);

    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    auto quickActionPanel = new QuickActionsPanel();
    quickActionPanel->setObjectName("QuickActionsPanel");

    auto toolsPanel = new ToolsPanel(tr("Tools"));
    toolsPanel->setObjectName("ToolsPanel");

    auto colorSelectorPanel = new ColorSelectorPanel();

    QWidget *sceneWindowContainer = QWidget::createWindowContainer(qt3DWindow, this);
    sceneWindowContainer->setObjectName("SceneWindow");

    gridLayout->addWidget(quickActionPanel, 0, 0, 1, -1);
    gridLayout->addWidget(toolsPanel, 1, 0, 1, 1, Qt::AlignTop);
    gridLayout->addWidget(sceneWindowContainer, 1, 1, 1, 1);
    gridLayout->addWidget(colorSelectorPanel, 2, 1, -1, -1);

    centralWidget->setLayout(gridLayout);

    this->setCentralWidget(centralWidget);
}

} // namespace TMC
