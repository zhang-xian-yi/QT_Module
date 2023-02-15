#pragma once

#include "AbstractLight.h"

class PointLight: public AbstractLight {
    Q_OBJECT

public:
    PointLight(QObject* parent = 0);
    PointLight(QVector3D color, QVector3D position, QObject* parent = 0);
    PointLight(const PointLight& light);
    ~PointLight();

    void dumpObjectInfo(int level = 0) override;
    void dumpObjectTree(int level = 0) override;

    bool visible() const;
    QVector3D position() const;
    bool enableAttenuation() const;
    QVector3D attenuationArguments() const;
    float attenuationQuadratic() const;
    float attenuationLinear() const;
    float attenuationConstant() const;
    QSharedPointer<Mesh> marker() const override;

public slots:
    void setEnabled(bool enabled) override;
    void setColor(QVector3D color) override;
    void setVisible(bool visible);
    void setPosition(QVector3D position);
    void setEnableAttenuation(bool enabled);
    void setAttenuationArguments(QVector3D value);
    void setAttenuationQuadratic(float value);
    void setAttenuationLinear(float value);
    void setAttenuationConstant(float value);

signals:
    void visibleChanged(bool visible);
    void positionChanged(QVector3D position);
    void enableAttenuationChanged(bool enabled);
    void attenuationArgumentsChanged(QVector3D value);
    void attenuationQuadraticChanged(float value);
    void attenuationLinearChanged(float value);
    void attenuationConstantChanged(float value);

protected:
    QVector3D m_position;
    bool m_enableAttenuation;
    float m_attenuationQuadratic, m_attenuationLinear, m_attenuationConstant;
    QSharedPointer<Mesh> m_marker;

    void initMarker();
};
