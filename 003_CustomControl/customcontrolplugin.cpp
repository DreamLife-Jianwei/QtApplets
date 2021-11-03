#include "customcontrol.h"
#include "customcontrolplugin.h"

#include <QtPlugin>

CustomControlPlugin::CustomControlPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void CustomControlPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CustomControlPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CustomControlPlugin::createWidget(QWidget *parent)
{
    return new CustomControl(parent);
}

QString CustomControlPlugin::name() const
{
    return QLatin1String("CustomControl");
}

QString CustomControlPlugin::group() const
{
    return QLatin1String("");
}

QIcon CustomControlPlugin::icon() const
{
    return QIcon(QLatin1String(":/logo.jpg"));
}

QString CustomControlPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CustomControlPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CustomControlPlugin::isContainer() const
{
    return false;
}

QString CustomControlPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomControl\" name=\"customControl\">\n</widget>\n");
}

QString CustomControlPlugin::includeFile() const
{
    return QLatin1String("customcontrol.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(customcontrol, CustomControlPlugin)
#endif // QT_VERSION < 0x050000
