#include "customcontrol.h"
#include "customcontrolplugin.h"

#include <QtPlugin>

CustomControlPlugin::CustomControlPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
    qRegisterMetaType<TestRect>("TestRect");

}
/**
 * @brief CustomControlPlugin::initialize
 * 初始化小部件以使用指定的formEditor接口
 */
void CustomControlPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here
    qRegisterMetaType<TestRect>("TestRect");
    m_initialized = true;
}
/**
 * @brief CustomControlPlugin::isInitialized
 * @return
 * 返回自定义控件的状态，如果已经被初始化了，返回true，否者返回false
 */
bool CustomControlPlugin::isInitialized() const
{
    return m_initialized;
}
/**
 * @brief CustomControlPlugin::createWidget
 * @param parent
 * @return
 * 使用给定的父类返回自定义小控件新实例
 */
QWidget *CustomControlPlugin::createWidget(QWidget *parent)
{
    qRegisterMetaType<TestRect>("TestRect");
    return new CustomControl(parent);
}
/**
 * @brief CustomControlPlugin::name
 * @return
 * 返回接口提供的自定义控件的类名，返回的名称必须与自定义控件使用的类名相同
 */
QString CustomControlPlugin::name() const
{
    return QLatin1String("CustomControl");
}
/**
 * @brief CustomControlPlugin::group
 * @return
 * 返回自定义小控件所属的组的名称
 */
QString CustomControlPlugin::group() const
{
    return QLatin1String("");
}
/**
 * @brief CustomControlPlugin::icon
 * @return
 * 这个将返回这个自定义控件的图标，用来在Qt Designer中表示这个控件
 */
QIcon CustomControlPlugin::icon() const
{
    return QIcon(QLatin1String(":/Images/logo2.png"));
}
/**
 * @brief CustomControlPlugin::toolTip
 * @return
 * 返回关于小控件的简短描述，可以在Qt Designer中看到
 */
QString CustomControlPlugin::toolTip() const
{
    return QLatin1String("");
}
/**
 * @brief CustomControlPlugin::whatsThis
 * @return
 * 在小控件的"what's this?" 帮助中返回可有Qt Designer使用的小控件的描述
 */
QString CustomControlPlugin::whatsThis() const
{
    return QLatin1String("");
}
/**
 * @brief CustomControlPlugin::isContainer
 * @return
 * 如果自定义的控件被当做容器使用，则返回true，否者返回false；大多数自定义的小控件并不用户保护其他小部件，因此他们对此函数的实现将返回false，但是自定义的容器将返回true，以确保他们在Qt Designer中正确运行。
 */
bool CustomControlPlugin::isContainer() const
{
    return false;
}
/**
 * @brief CustomControlPlugin::domXml
 * @return
 * 将用于描述自定义控件属性的XML返回给Qt Designer
 */
QString CustomControlPlugin::domXml() const
{
    return QLatin1String("<widget class=\"CustomControl\" name=\"customControl\">\n</widget>\n");
}
/**
 * @brief CustomControlPlugin::includeFile
 * @return
 * 返回UIC在自定义小控件创建代码时使用的包含文件的路径。
 */
QString CustomControlPlugin::includeFile() const
{
    return QLatin1String("customcontrol.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(customcontrol, CustomControlPlugin)
#endif // QT_VERSION < 0x050000
