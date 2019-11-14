//
//  SMMMessage.h
//  Lithium
//

#import <UIKit/UIKit.h>
#import "SMMCoordinates.h"
#import "SMMDisplaySettings.h"

/**
 *  @abstract Notification that is fired when a message fails to upload.
 */
extern NSString* _Nonnull const SMMMessageUploadFailedNotification;

/**
 *  @abstract Notification that is fired when a message uploads successfully.
 */
extern NSString* _Nonnull const SMMMessageUploadCompletedNotification;

/**
 *  @abstract A type of message that contains an image, text, and/or action buttons
 */
extern NSString* _Nonnull const SMMMessageTypeImage;

/**
 *  @abstract A type of message that contains text and/or action buttons
 */
extern NSString* _Nonnull const SMMMessageTypeText;

/**
 *  @abstract A type of message that contains a location
 */
extern NSString* _Nonnull const SMMMessageTypeLocation;

/**
 *  @abstract A type of message that contains a file and/or text
 */
extern NSString* _Nonnull const SMMMessageTypeFile;

/**
 *  @abstract A type of message that contains a horizontally scrollable set of items
 */
extern NSString* _Nonnull const SMMMessageTypeCarousel;

/**
 *  @abstract A type of message that contains a vertically scrollable set of items
 */
extern NSString* _Nonnull const SMMMessageTypeList;

/**
 *  @discussion Upload status of an SMMMessage.
 *
 *  @see SMMMessage
 */
typedef NS_ENUM(NSInteger, SMMMessageUploadStatus) {
    /**
     *  A user message that has not yet finished uploading.
     */
    SMMMessageUploadStatusUnsent,
    /**
     *  A user message that failed to upload.
     */
    SMMMessageUploadStatusFailed,
    /**
     *  A user message that was successfully uploaded.
     */
    SMMMessageUploadStatusSent,
    /**
     *  A message that did not originate from the current user.
     */
    SMMMessageUploadStatusNotUserMessage
};

@interface SMMMessage : NSObject

/**
 *  @abstract Create a message with the given text. The message will be owned by the current user.
 */
-(nonnull instancetype)initWithText:(nonnull NSString*)text;

/**
 *  @abstract Create a message with the given text, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithText:(nonnull NSString *)text payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract Create a message with the given coordinates, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithCoordinates:(nonnull SMMCoordinates *)coordinates payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract The unique identifier of the message. May be nil if a unique identifier has not been generated for this message
 */
@property(readonly, nullable) NSString* messageId;

/**
 *  @abstract The text content of the message. May be nil if mediaUrl or actions are provided
 */
@property(nullable) NSString* text;

/**
 *  @abstract The text fallback to display for message types not supported by the SDK. May be nil
 */
@property(nullable) NSString* textFallback;

/**
 *  @abstract The name of the author. This property may be nil if no name could be determined.
 */
@property(nullable) NSString* name;

/**
 *  @abstract The url for the author's avatar image. May be nil
 */
@property(nullable) NSString* avatarUrl;

/**
 *  @abstract The date and time the message was sent
 */
@property(nullable) NSDate *date;

/**
 *  @abstract Returns YES if the message originated from the user, or NO if the message comes from the app team.
 */
@property(readonly) BOOL isFromCurrentUser;

/**
 *  @abstract The upload status of the message.
 *
 *  @see SMMMessageStatus
 */
@property(readonly) SMMMessageUploadStatus uploadStatus;

/**
 *  @abstract An array of SMMMessageAction objects representing the actions associated with this message (if any)
 *
 *  @discussion This array may be nil or empty, so check the length of the array to know if a message has actions or not.
 *
 *  @see SMMMessageAction
 */
@property(readonly, nullable) NSArray* actions;

/**
 *  @abstract An array of SMMMessageItem objects representing the items associated with this message
 *
 *  @discussion Only messages of type `SMMMessageTypeCarousel` and `SMMMessageTypeList` contain items.
 *
 *  @see SMMMessageItem
 */
@property(readonly, nullable) NSArray* items;

/**
 *  @abstract The url to the media asset, if applicable. Returns nil if the message is not an image or file message.
 */
@property(nullable) NSString* mediaUrl;

/**
 *  @abstract The size of the media asset in bytes. May be nil.
 */
@property(nullable) NSNumber* mediaSize;

/**
 *  @abstract The type the message.
 *
 *  @discussion Valid types include SMMMessageTypeText, SMMMessageTypeImage, and SMMMessageTypeLocation
 */
@property(nullable) NSString* type;

/**
 *  @abstract Coordinates for a location for a message of type SMMMessageTypeLocation
 */
@property(readonly, nullable) SMMCoordinates *coordinates;

/**
 *  @abstract Settings to adjust the layout of a message of type SMMMessageTypeCarousel
 *
 *  @see SMMDisplaySettings
 */
@property(readonly, nullable) SMMDisplaySettings *displaySettings;

/**
 *  @abstract The role of the message.
 *
 *  @discussion Valid roles include `appUser`, `appMaker`, and `whisper`. Messages created with -initWithText: have role of `appUser`.
 */
@property(readonly, nullable) NSString* role;

/**
 *  @abstract Metadata associated with the message.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract The payload of an action with type SMMMessageActionTypeReply
 *
 *  @discussion The payload of a SMMMessageActionTypeReply, if applicable. May be nil
 */
@property(nullable) NSString* payload;

@end
