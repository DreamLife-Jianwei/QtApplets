CONFIG      += plugin debug_and_release             #config用来告诉qmake关于应用程序的配置信息，静态插件添加为plugin static

TARGET      = $$qtLibraryTarget(customcontrol)      #TARGET变量指定生成的目标库文件的名字，如果生成的是应用程序，这对应指的是应用程序的名称

TEMPLATE    = lib                                   #模块设置，lib是指生成lib库，app指生成应用程序(默认)

HEADERS     = customcontrolplugin.h \                 #包含头文件
    testrect.h

SOURCES     = customcontrolplugin.cpp \               #包含源文件
    testrect.cpp

RESOURCES   = images.qrc                            #资源文件

LIBS        += -L.                                  #包含库

greaterThan(QT_MAJOR_VERSION, 4) {                  #这个就是不同版本Qt添加Designer模块的对应方法，当Qt版本大于4是，使用QT += designer 否则使用 CONFIG += designer
    QT += designer
} else {
    CONFIG += designer
}
# 插件安装，这里我暂时也不是很理解
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(customcontrol.pri)			#这个应该就是真正的控件包含了，这里包含了一个customcontrol的控件，  不知道 这么理解是否正确

QT += widgets
