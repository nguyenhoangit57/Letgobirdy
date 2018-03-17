//
//  Admob.cpp


#include "Admob.h"
#include "cocos2d.h"
using namespace std;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOSWrapper.h"
#endif
#include "AdmodAndroid.h"
static Admob _sAdmobManager;

Admob* Admob::getInstance() {
    return &_sAdmobManager;
}

void Admob::init(const std::string &bannerId, const std::string &interstitialId) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::getInstance()->init(bannerId, interstitialId);
#endif
}

void Admob::showBanner(AdmobPosition position) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::getInstance()->showBanner((int)position);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::showBanner();
#endif
}

void Admob::hideBanner() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::getInstance()->hideBanner();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::hideBanner();
#endif
}

void Admob::loadInterstitial() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::getInstance()->loadInterstitial();
#endif
}

void Admob::showInterstitial() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    IOSWrapper::getInstance()->showInterstitial();
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::showFullAdvertiment();
#endif
}
