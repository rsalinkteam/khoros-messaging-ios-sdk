# [Khoros Messaging](http://www.khoros.com)


[![Pod Version](https://img.shields.io/badge/Version-0.0.1-8e8e8e)](https://github.com/lithiumtech/khoros-messaging-ios-sdk)
[![Platform](https://img.shields.io/badge/Platform-iOS-8e8e8e)](https://github.com/lithiumtech/khoros-messaging-ios-sdk)
[![License](https://img.shields.io/badge/License-Website-8e8e8e)](https://www.khoros.com/privacy)

Khoros Messaging iOS SDK


Add KhorosMessaging to podfile:

    pod 'KhorosMessaging', :git => 'git@github.com:lithiumtech/khoros-messaging-ios-sdk.git', :tag => '0.0.1'

Import Lithium:

```Swift
    import Lithium
```

Use:

```Swift
Lithium.initWith(SMMSettings(appId: "YOUR_APP_ID")) { (error: Error?, userInfo: [AnyHashable : Any]?) in
            // Your code after init is complete
        }
Lithium.show()
```
