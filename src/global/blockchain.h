#ifndef TMC_BLOCKCHAIN_H
#define TMC_BLOCKCHAIN_H

namespace TMC {

class Vec3i;
class AxisVec3i;

/* Blockchain represents coordinates and dimenstions of a 1x1xN
 * row of blocks by any axis, conveniently packed. */
class Blockchain {
public:
    Blockchain(Vec3i basePos, AxisVec3i range);

    Vec3i getBasePos();
    void setBasePos(Vec3i newBasePos);

    AxisVec3i getRange();
    void setRange(AxisVec3i newRange);

private:
    Vec3i m_basePos; // Blockchain has a base block and it occupies some area by one axis (range)
    AxisVec3i m_range;
};

}

#endif // TMC_BLOCKCHAIN_H