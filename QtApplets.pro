TEMPLATE = subdirs

SUBDIRS += \
#    001_GetProcessOwner \          #这个子项目需要用的vs编译，我日常用的是MinGW，所以先注释掉
    002_GetUserName \
    003_CustomControl \
    004_QSettingsTimer \
    005_International \
    006_Q_ASSERT_Demo \
    007_QSignalMapperDemo \
    008_Log4QtDemo
