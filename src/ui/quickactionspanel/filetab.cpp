#include <QHBoxLayout>
#include <QToolButton>

#include "filetab.h"

namespace TMC {

FileTab::FileTab(QWidget *parent)
    : BaseQuickActionsTab(parent, "File") {
    auto newButton = new QToolButton();
    newButton->setIcon(QIcon(":/icons/new_file_ic.png"));
    newButton->setToolTip(tr("New File"));

    auto openButton = new QToolButton();
    openButton->setIcon(QIcon(":/icons/open_file_ic.png"));
    openButton->setToolTip(tr("Open File"));

    auto saveButton = new QToolButton();
    saveButton->setIcon(QIcon(":/icons/save_ic.png"));
    saveButton->setToolTip(tr("Save File"));

    m_layout->addWidget(newButton);
    m_layout->addWidget(openButton);
    m_layout->addWidget(saveButton);
}

} // namespace TMC
