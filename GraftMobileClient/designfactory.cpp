#include "designfactory.h"

#include <QQmlContext>
#include <QQmlEngine>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QColor>
#endif

DesignFactory::DesignFactory(QObject *parent) : QObject(parent)
{
    mColors.insert(Foreground, QStringLiteral("#34435b"));
    mColors.insert(IosNavigationBar, QStringLiteral("#394558"));
    mColors.insert(CircleBackground, QStringLiteral("#4fb67a"));
    mColors.insert(Highlighting, QStringLiteral("#ecf4ef"));
    mColors.insert(ItemHighlighting, QStringLiteral("#fedbb4"));
    mColors.insert(AndroidMainText, QStringLiteral("#404040"));
    mColors.insert(IosMainText, QStringLiteral("#000000"));
    mColors.insert(AndroidItemText, QStringLiteral("#9e9e9e"));
    mColors.insert(IosItemText, QStringLiteral("#797979"));
    mColors.insert(LightText, QStringLiteral("#ffffff"));
    mColors.insert(CartLabel, QStringLiteral("#fe4200"));
    mColors.insert(AllocateLine, QStringLiteral("#e6e6e8"));
    mColors.insert(AndroidStatusBar, QStringLiteral("#233146"));
    init();
}

QString DesignFactory::color(DesignFactory::ColorTypes type) const
{
    return mColors.value(type);
}

void DesignFactory::registrate(QQmlContext *context)
{
    qmlRegisterType<DesignFactory>("com.graft.design", 1, 0, "DesignFactory");
    context->setContextProperty(QStringLiteral("ColorFactory"), this);
}

void DesignFactory::init()
{
#ifdef Q_OS_ANDROID
    if (QtAndroid::androidSdkVersion() >= 21)
    {
        QtAndroid::runOnAndroidThread([=]() {
            QAndroidJniObject window = QtAndroid::androidActivity().callObjectMethod(
                        "getWindow","()Landroid/view/Window;");
            window.callMethod<void>("addFlags", "(I)V", 0x80000000);
            window.callMethod<void>("clearFlags", "(I)V", 0x04000000);
            window.callMethod<void>("setStatusBarColor", "(I)V",
                                    QColor(color(AndroidStatusBar)).rgba());
        });
    }
#endif
}
