//
//  AdmobIOSWrapper.m
//  PikachuSpace
//
//  Created by Hoang Nguyen on 1/27/17.
//
//

#import "IOSWrapper.h"
#import "AdmobIOS.h"

static IOSWrapper _IOSWrapper;

IOSWrapper* IOSWrapper::getInstance() {
    return &_IOSWrapper;
}

void IOSWrapper::init(const std::string &bannerId, const std::string &interstitialId) {
    NSString *banner = [NSString stringWithUTF8String:bannerId.data()];
    NSString* interstitial = [NSString stringWithUTF8String:interstitialId.data()];
    [[AdmobIOS sharedAdmob] setBannerId:banner];
    [[AdmobIOS sharedAdmob] setInterstitialId:interstitial];
}


void IOSWrapper::showBanner(int position) {
    [[AdmobIOS sharedAdmob] showBannerInPostion:position];
}

void IOSWrapper::hideBanner() {
    [[AdmobIOS sharedAdmob] hideBanner];
}

void IOSWrapper::loadInterstitial() {
    [[AdmobIOS sharedAdmob] loadInterstitial];
}

void IOSWrapper::showInterstitial() {
    [[AdmobIOS sharedAdmob] showInterstitial];
}


