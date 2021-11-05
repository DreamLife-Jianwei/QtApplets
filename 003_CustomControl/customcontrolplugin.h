#ifndef CUSTOMCONTROLPLUGIN_H
#define CUSTOMCONTROLPLUGIN_H

#include <QDesignerCustomWidgetInterface>                   //使Qt Designer能够访问和构造自定义小部件

class CustomControlPlugin : public QObject, public QDesignerCustomWidgetInterface       //继承QObject和QDesignerCustomWidgetInterface
{
    Q_OBJECT                                                //包含 Q_OBJECT宏

    Q_INTERFACES(QDesignerCustomWidgetInterface)            //这个宏将告诉Qt这个类实现了那些接口，这个宏在实现插件是使用

#if QT_VERSION >= 0x050000                                  //判断Qt版本是否大于5

    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")       //此宏用于声明元数据，该元数据是实例化此对象的插件的一部分
                                                                                    //这个宏需要声明通过对象实现的接口的IID，并应用包含插件的数据文件
                                                                                    //在Qt插件的源代码中，这个宏应该只出现一次
#endif // QT_VERSION >= 0x050000

public:
    /**
     * @brief CustomControlPlugin
     * @param parent
     * 构造函数
     */
    CustomControlPlugin(QObject *parent = 0);
    /**
     * @brief isContainer
     * @return
     * 如果自定义的控件被当做容器使用，则返回true，否者返回false；
     * 大多数自定义的小控件并不用户保护其他小部件，因此他们对此函数的实现将返回false，但是自定义的容器将返回true，以确保他们在Qt Designer中正确运行。
     */
    bool isContainer() const;
    /**
     * @brief isInitialized
     * @return
     * 返回自定义控件的状态，如果已经被初始化了，返回true，否者返回false
     */
    bool isInitialized() const;
    /**
     * @brief icon
     * @return
     * 这个将返回这个自定义控件的图标，用来在Qt Designer中表示这个控件
     */
    QIcon icon() const;
    /**
     * @brief domXml
     * @return
     * 将用于描述自定义控件属性的XML返回给Qt Designer
     */
    QString domXml() const;
    /**
     * @brief group
     * @return
     * 返回自定义小控件所属的组的名称
     */
    QString group() const;
    /**
     * @brief includeFile
     * @return
     * 返回UIC在自定义小控件创建代码时使用的包含文件的路径。
     */
    QString includeFile() const;
    /**
     * @brief name
     * @return
     * 返回接口提供的自定义控件的类名，
     * 返回的名称必须与自定义控件使用的类名相同
     */
    QString name() const;
    /**
     * @brief toolTip
     * @return
     * 返回关于小控件的简短描述，可以在Qt Designer中看到
     */
    QString toolTip() const;
    /**
     * @brief whatsThis
     * @return
     * 在小控件的"what's this?" 帮助中返回可有Qt Designer使用的小控件的描述
     */
    QString whatsThis() const;
    /**
     * @brief createWidget
     * @param parent
     * @return
     * 使用给定的父类返回自定义小控件新实例
     */
    QWidget *createWidget(QWidget *parent);
    /**
     * @brief initialize
     * @param core
     * 初始化小部件以使用指定的formEditor接口
     */
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;             //控件初始化标志位
};

#endif // CUSTOMCONTROLPLUGIN_H
