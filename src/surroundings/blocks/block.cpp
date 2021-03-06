#include <Qt3DExtras/QPhongMaterial>

#include <cmath>

#include "block.h"
#include "customalphaphong.h"
#include "phantommaterial.h"

namespace TMC {

Block::Block(Vec3i discretePos, Qt3DCore::QEntity *parent, BlockType type, HidedState isHided, LockedState isLocked)
    : m_type(type)
    , m_discretePos(discretePos)
    , m_hided(isHided)
    , m_locked(isLocked)
    , m_blockEntity(new Qt3DCore::QEntity())
    , m_blockTransform(nullptr)
    , m_blockMesh(nullptr)
    , m_blockMaterial(nullptr) {

    m_blockEntity->setParent(parent);

    QObject::connect(this, SIGNAL(hidedChanged()),
                                  this, SLOT(updateScale()));

    if (type != PLACEHOLDER_BLOCK) {
        m_blockTransform = new Qt3DCore::QTransform();
        m_blockMesh = new Qt3DExtras::QCuboidMesh();

        // Calling these methods manually
        this->updateScale();
        this->updateBaseTranslation();

        m_blockTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 0), 0.0f));

        switch (type) {
            case DEFAULT_BLOCK:
                m_blockMaterial = new Qt3DExtras::QPhongMaterial();
                break;
            case DEFAULT_TRANSP_BLOCK:
                m_blockMaterial = new CustomAlphaPhong();
                break;
            case PHANTOM_BLOCK:
                m_blockMaterial = new PhantomMaterial();
                break;
        }

        m_blockEntity->addComponent(m_blockTransform);
        m_blockEntity->addComponent(m_blockMesh);
        m_blockEntity->addComponent(m_blockMaterial);
    }

    qDebug() << "Block created:" << m_discretePos << "\tType:" << m_type;
}

Block::~Block() {
    if (m_blockEntity != nullptr) {
        // Deleting automatically notifies QEnity's parents and all connections
        // that it was deleted in QNode and QObject destructors
        delete m_blockEntity;
    }
    qDebug() << "Block destroyed:" << m_discretePos << "\tType:" << m_type;
}


Vec3i Block::worldToDiscreteCoordinates(QVector3D worldCoordinates) {
    return Vec3i(round(worldCoordinates.x() / BLOCK_LENGTH),
                 round(worldCoordinates.y() / BLOCK_LENGTH),
                 round(worldCoordinates.z() / BLOCK_LENGTH));
}

QVector3D Block::discreteToWorldCoordinates(Vec3i discreteCoordinates) {
    return QVector3D(discreteCoordinates.x() * BLOCK_LENGTH,
                     discreteCoordinates.y() * BLOCK_LENGTH,
                     discreteCoordinates.z() * BLOCK_LENGTH);
}


BlockType Block::getBlockType() const {
    return m_type;
}

bool Block::isHided() const {
    return m_hided;
}

void Block::setHided(bool hided) {
    if (m_hided == hided) return;

    m_hided = hided;
    emit hidedChanged();
}

bool Block::isLocked() const {
    return m_locked;
}

void Block::setLocked(bool isLocked) {
    m_locked = isLocked;
}

Vec3i Block::getDiscretePos() const {
    return m_discretePos;
}

void Block::setDiscretePos(Vec3i newDiscretePos) {
    if (m_discretePos == newDiscretePos) return;

    m_discretePos = newDiscretePos;
    updateBaseTranslation();
}

// Translate transform from it's base (according to m_discretePos) scene position
void Block::translateFromBasePos(QMatrix4x4 translMatr) {
    if (m_blockTransform == nullptr) return;

    updateBaseTranslation();
    m_blockTransform->setMatrix(m_blockTransform->matrix() * translMatr);
}

void Block::updateScale() {
    if (m_blockTransform == nullptr) return;

    const float transfScale = m_hided ? 0.0f : 1.0f;
    m_blockTransform->setScale(transfScale);
}

// Calculates transform's translation according to block's position in scene
void Block::updateBaseTranslation() {
    if (m_blockTransform == nullptr) return;

    QVector3D newTranslation = this->discreteToWorldCoordinates(m_discretePos);
    m_blockTransform->setTranslation(newTranslation);
}

}
