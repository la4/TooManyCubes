#ifndef TMC_CUSTOMALPHAPHONG_H
#define TMC_CUSTOMALPHAPHONG_H

#include <Qt3DExtras>

namespace TooManyCubes {

class CustomAlphaPhong : public Qt3DExtras::QPhongAlphaMaterial {
public:
    CustomAlphaPhong();
};

}

#endif // TMC_CUSTOMALPHAPHONG_H