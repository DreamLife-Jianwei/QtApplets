#include "myhook.h"

#include <QSettings>
#include <QApplication>

/**
 * 新增注册表内容
 */
#define TASKMANAGERSystem "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
#define TASKMANAGERExplorer "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"

HHOOK mKeyHook = NULL;
HHOOK mMouseHook = NULL;

/**
 * @brief keyProc
 * @param nCode
 * @param wParam
 * @param lParam
 * @return
 * 键盘钩子过程
 */
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    //在WH_KEYBOARD_LL模式下lParam 是指向KBDLLHOOKSTRUCT类型地址
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    //如果nCode等于HC_ACTION则处理该消息，如果小于0，则钩子子程就必须将该消息传递给 CallNextHookEx
    if(nCode == HC_ACTION)
    {
        if(pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL)& 0x8000 && GetAsyncKeyState(VK_SHIFT)&0x8000)             //屏蔽 "Ctrl+Shift+Esc"
            return 1;
        if(pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000)                                                 //屏蔽 "Ctrl+Esc"
            return 1;
        if(pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN)                                                             //屏蔽 "Alt+Tab"
            return 1;
        if(pkbhs->vkCode == VK_ESCAPE && pkbhs->flags &LLKHF_ALTDOWN)                                                           //屏蔽 "Alt+Esc"
            return 1;
        if(pkbhs->vkCode == VK_LWIN || pkbhs->vkCode == VK_RWIN)                                                                //屏蔽 "LWIN/RWIN"
            return 1;
        if(pkbhs->vkCode == VK_F4 && pkbhs->flags & LLKHF_ALTDOWN)                                                              //屏蔽 "Alt+F4"
            return 1;
    }
    return CallNextHookEx(mKeyHook, nCode, wParam, lParam);
}

/**
 * @brief mouseProc
 * @param nCode
 * @param wParam
 * @param lParam
 * @return
 * 鼠标钩子过程
 */
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    Q_UNUSED(nCode);
    Q_UNUSED(wParam);
    Q_UNUSED(lParam);

    return 1;
}

MyHook::MyHook(QObject *parent) : QObject{parent}
{

}

MyHook::~MyHook()
{

}
/**
 * @brief MyHook::setAllEnable
 * @param flag
 * 设置是否启用屏蔽键盘
 */
void MyHook::setAllEnable(bool flag)
{
    hook(flag);
//    closeTaskManager(flag);
    closeTaskWindow(flag);
}

/**
 * @brief MyHook::hook
 * @param flag
 * 安装钩子
 */
void MyHook::hook(bool flag)
{
    if (flag)
    {
        //这两个底层钩子,不要DLL就可以全局
        //底层键盘钩子
        mKeyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
        //底层鼠标钩子
        //    mMouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
    }
    else
    {
        UnhookWindowsHookEx(mKeyHook);
        //  UnhookWindowsHookEx(mMouseHook);
    }
}

/**
 * @brief MyHook::closeTaskManager
 * @param flag
 * 关闭任务管理器 和 桌面
 */
void MyHook::closeTaskWindow(bool flag)
{
    if (!flag)
    {
        ShowWindow(mTask, SW_SHOW);
        ShowWindow(mDesktop, SW_SHOW);                  //显示
    }
    else
    {
        mTask=FindWindow(L"Shell_TrayWnd",NULL);
        mDesktop = FindWindow(L"ProgMan", NULL);
        ShowWindow(mTask,SW_HIDE);
        ShowWindow(mDesktop, SW_HIDE);                  //隐藏桌面
    }
}

/**
 * @brief MyHook::closeTaskWindow
 * @param flag
 * 添加注册屏蔽Ctrl+Alt+del
 */
void MyHook::closeTaskManager(bool flag)
{
    /**
     *                              ☆特别注意☆
     * 屏蔽ctrl + alt +del 需要修改注册表的值， 取得管理员权限， 关闭360等杀毒软件
     */
    int value = flag ? 0x00000001 : 0x00000000;
    QSettings *settings = new QSettings(TASKMANAGERSystem, QSettings::NativeFormat);
    settings->setValue("DisableTaskMgr", value);                                                //任务管理器
    settings->setValue("DisableChangePassword", value);                                         //更改密码
    settings->setValue("DisableLockWorkstation", value);                                        //锁定计算机
    settings->setValue("DisableSwitchUserOption", value);                                       //切换用户
    QSettings *settings2 = new QSettings(TASKMANAGERExplorer, QSettings::NativeFormat);
    settings2->setValue("NoLogOff", value);                                                     //注销
    delete settings;
    delete settings2;
}

