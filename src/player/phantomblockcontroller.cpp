#include <Qt3DLogic>
#include <Qt3DRender>

#include "phantomblockcontroller.h"
#include "scene.h"
#include "phantomblock.h"

namespace TMC {

PhantomBlockController::PhantomBlockController(Scene *scene, const Qt3DRender::QCamera *playerCamera)
    : Qt3DCore::QEntity(scene->getRootEntity())
    , m_scene(scene)
    , m_phantomBlock(new PhantomBlock(scene->getRootEntity()))
    , m_camera(playerCamera)
    , m_frameAction(new Qt3DLogic::QFrameAction()) {

    QObject::connect(m_frameAction, SIGNAL(triggered(float)),
                     this, SLOT(onTriggered(float)));

    this->addComponent(m_frameAction);
}

PhantomBlockController::~PhantomBlockController() {
}

Vec3i PhantomBlockController::getPhantomBlockPos() {
    return m_phantomBlock->getDiscretePos();
}

void PhantomBlockController::onTriggered(float) {
    // TODO: implement smart block placer
    if (m_camera != nullptr) {
        Vec3i newDiscretePos = Block::worldToDiscreteCoordinates(
                    m_camera->position() + m_camera->viewVector() / m_camera->viewVector().length() * PHANTOM_BLOCK_DISTANCE);

        HidedState hidedState = m_scene->blockCouldBePlacedManually(newDiscretePos) ? BLOCK_VISIBLE : BLOCK_HIDED;

        m_phantomBlock->setHided(hidedState);
        m_phantomBlock->setDiscretePos(newDiscretePos);
    }
}

}
