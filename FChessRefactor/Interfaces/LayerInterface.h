#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include <QImage>

class LayerInterface
{
public:
    virtual const QImage& LayerImage() = 0;
};

#endif // LAYERINTERFACE_H
