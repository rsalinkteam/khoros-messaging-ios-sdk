Pod::Spec.new do |s|
  s.name                  = "KhorosMessaging"
  s.version               = "2.1.1"
  s.summary               = "summary"
  s.homepage              = "homepage"
  s.author                = { "Khoros" => "pkwak@khoros.com" }
  s.source                = { :git => "git@github.com:lithiumtech/messaging-ios.git", :tag =>"#{s.version}" }
  s.license               = { :type => "Commercial", :text => "https://www.khoros.com/privacy" }
  s.source_files          = "Lithium.framework/Headers/Lithium.h", "Lithium.framework/Headers/SMMSettings.h", "Lithium.framework/Headers/SMMUser.h", "Lithium.framework/Headers/SMMConversation.h", "Lithium.framework/Headers/SMMMessage.h", "Lithium.framework/Headers/SMMMessageAction.h", "Lithium.framework/Headers/SMMConversationActivity.h", "Lithium.framework/Headers/SMMCoordinates.h"
  s.preserve_paths        = "Lithium.framework/*"
  s.module_map            = "Lithium.framework/Modules/module.modulemap"
  s.frameworks            = "CoreText", "SystemConfiguration", "CoreTelephony", "Foundation", "CoreGraphics", "UIKit", "QuartzCore", "AssetsLibrary", "Photos", "AVFoundation", "CFNetwork"
  s.library               = "icucore"
  s.xcconfig              = { "FRAMEWORK_SEARCH_PATHS" => "$(PODS_ROOT)/KhorosMessaging" }
  s.vendored_frameworks   = "Lithium.framework"
  s.requires_arc          = true
  s.platform              = :ios
  s.ios.deployment_target = '8.0'
end
