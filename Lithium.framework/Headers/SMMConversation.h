//
//  SMMConversation.h
//  Lithium
//

#import <Foundation/Foundation.h>
#import "SMMMessage.h"
#import "SMMMessageAction.h"
#import "SMMMessageItem.h"
#import "SMMConversationActivity.h"

NS_ASSUME_NONNULL_BEGIN
@protocol SMMConversationDelegate;

typedef void (^SMMImageUploadProgressBlock)(double progress);
typedef void (^SMMImageUploadCompletionBlock)(NSError* _Nullable error, SMMMessage* _Nullable message);
typedef void (^SMMFileUploadProgressBlock)(double progress);
typedef void (^SMMFileUploadCompletionBlock)(NSError* _Nullable error, SMMMessage* _Nullable message);

/**
 *  @discussion Represents various actions the user takes when interacting with Lithium UI components.
 */
typedef NS_ENUM(NSInteger, SMMAction) {
    /**
     *  The user has tapped on a Lithium in-app notification.
     */
    SMMActionInAppNotificationTapped,
    /**
     *  The user has tapped on a Lithium push notification.
     */
    SMMActionPushNotificationTapped
};

/**
 *  @abstract Posted when the count of unread messages changes. The notification object will be an instance of SMMConversation, of which you can then inspect the messageCount property.
 *
 *  @see SMMConversation
 */
extern NSString* const SMMConversationUnreadCountDidChangeNotification;

/**
 *  @abstract Posted when an image upload begins.
 *
 *  @discussion The userInfo dictionary contains the UIImage to upload. Use SMMConversationImageKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMConversationImageKey
 */
extern NSString* const SMMConversationImageUploadDidStartNotification;

/**
 *  @abstract Posted when an image upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the UIImage being uploaded, as well as an NSNumber reflecting the current progress. Use SMMConversationImageKey and SMMConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMConversationImageKey
 *  @see SMMConversationProgressKey
 */
extern NSString* const SMMConversationImageUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when an image upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the UIImage that was uploaded. Use SMMConversationImageKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the SMMMessage instance of the new message. Use SMMConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use SMMConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMMessage
 *  @see SMMConversationImageKey
 *  @see SMMConversationMessageKey
 *  @see SMMConversationErrorKey
 */
extern NSString* const SMMConversationImageUploadCompletedNotification;

/**
 *  @abstract Posted when a file upload begins.
 *
 *  @discussion The userInfo dictionary contains the url of the file to upload. Use SMMConversationFileKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMConversationFileKey
 */
extern NSString* const SMMConversationFileUploadDidStartNotification;

/**
 *  @abstract Posted when a file upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the url of the file being uploaded, as well as an NSNumber reflecting the current progress. Use SMMConversationFileKey and SMMConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMConversationFileKey
 *  @see SMMConversationProgressKey
 */
extern NSString* const SMMConversationFileUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when a file upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the url of the file that was uploaded. Use SMMConversationFileKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the SMMMessage instance of the new message. Use SMMConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use SMMConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see SMMMessage
 *  @see SMMConversationFileKey
 *  @see SMMConversationMessageKey
 *  @see SMMConversationErrorKey
 */
extern NSString* const SMMConversationFileUploadCompletedNotification;

/**
 *  @abstract Posted when new messages are received from the server.
 *
 *  @discussion The userInfo dictionary contains an NSArray of SMMMessage objects. Use SMMConversationNewMessagesKey to access this value.
 *
 *  @see SMMMessage
 *  @see SMMConversationNewMessagesKey
 */
extern NSString* const SMMConversationDidReceiveMessagesNotification;

/**
 *  @abstract Posted when an operation to load previous messages in a conversation has been completed
 *
 *  @discussion This notification is posted as the result of [SMMConversation loadPreviousMessages]
 *
 *  If the operation succeeded, the object returned by this notification will include the updated array of messages
 *  If the operation failed, the userInfo dictionary will contain an "error" object with the response error
 *
 *  @see SMMMessage
 *  @see SMMConversationPreviousMessagesKey
 */
extern NSString* const SMMConversationDidReceivePreviousMessagesNotification;

/**
 *  @abstract Posted when a conversation activity has been created, such as typing start/stop
 *
 *  @see SMMConversationActivity
 *  @see SMMConversationActivityKey
 */
extern NSString* const SMMConversationDidReceiveActivityNotification;

/**
 *  @abstract A key whose value is an NSArray of SMMMessage objects.
 *
 *  @discussion This key is used with SMMConversationDidReceiveMessagesNotification notification.
 *
 *  @see SMMConversationDidReceiveMessagesNotification
 */
extern NSString* const SMMConversationNewMessagesKey;

/**
 *  @abstract A key whose value is an NSArray of SMMMessage objects
 *
 *  @discussion This key is used with SMMConversationDidReceivePreviousMessagesNotification notification
 *
 *  @see SMMConversationDidReceivePreviousMessagesNotification
 */
extern NSString* const SMMConversationPreviousMessagesKey;

/**
 *  @abstract A key whose value is a UIImage which represents an image being uploaded.
 *
 *  @discussion This key is used with SMMConversationImageUploadDidStartNotification, SMMConversationImageUploadProgressDidChangeNotification, and SMMConversationImageUploadCompletedNotification notifications.
 *
 *  @see SMMConversationImageUploadDidStartNotification
 *  @see SMMConversationImageUploadProgressDidChangeNotification
 *  @see SMMConversationImageUploadCompletedNotification
 */
extern NSString* const SMMConversationImageKey;

/**
 *  @abstract A key whose value is an NSURL which represents a file being uploaded.
 *
 *  @discussion This key is used with SMMConversationFileUploadDidStartNotification, SMMConversationFileUploadProgressDidChangeNotification, and SMMConversationFileUploadCompletedNotification notifications.
 *
 *  @see SMMConversationFileUploadDidStartNotification
 *  @see SMMConversationFileUploadProgressDidChangeNotification
 *  @see SMMConversationFileUploadCompletedNotification
 */
extern NSString* const SMMConversationFileKey;

/**
 *  @abstract A key whose value is an NSError.
 *
 *  @discussion This key is used with SMMConversationImageUploadCompletedNotification notification.
 *
 *  @see SMMConversationImageUploadCompletedNotification
 */
extern NSString* const SMMConversationErrorKey;

/**
 *  @abstract A key whose value is an SMMMessage object representing the newly created message.
 *
 *  @discussion This key is used with SMMConversationImageUploadCompletedNotification notification.
 *
 *  @see SMMConversationImageUploadCompletedNotification
 */
extern NSString* const SMMConversationMessageKey;

/**
 *  @abstract A key whose value is an NSNumber reflecting the current progress of an image upload.
 *
 *  @discussion This key is used with SMMConversationImageUploadProgressDidChangeNotification notification.
 *
 *  @see SMMConversationImageUploadProgressDidChangeNotification
 */
extern NSString* const SMMConversationProgressKey;

/**
 *  @abstract A key whose value is a SMMConversationActivity object representing the newly created activity
 *
 *  @discussion This key is used with SMMConversationDidReceiveActivityNotification notification.
 *
 *  @see SMMConversationDidReceiveActivityNotification
 */
extern NSString* const SMMConversationActivityKey;

/**
 *  @discussion The SMMConversation class provides an interface to interact with the current user's conversation.
 *
 *  To obtain an instance, use `[Lithium conversation]`. +initWithSettings:completionHandler: must have been called prior to retrieving the shared conversation object.
 *
 *  To send a message, use -sendMessage: with an SMMMessage object
 *
 *  Example:
 *
 *  `[[Lithium conversation] sendMessage:[[SMMMessage alloc] initWithText:@"Hello World!"]];`
 *
 *  A notification will be fired indicating the success or failure of the message. To subscribe to these notifications, use NSNotificationCenter.
 *
 *  Example:
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageUploaded:) name:SMMMessageUploadCompletedNotification object:nil];`
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageFailed:) name:SMMMessageUploadFailedNotification object:nil];`
 *
 *  @see SMMMessage
 *  @see Lithium
 */
@interface SMMConversation : NSObject

/**
 *  @abstract The unique identifier of the conversation. May be nil if a conversation doesn't exist for the current user
 */
@property(readonly, nullable) NSString* conversationId;

/**
 *  @abstract The array of SMMMessage objects representing the conversation.
 *
 *  @see SMMMessage
 */
@property(readonly, nullable) NSArray* messages;

/**
 *  @abstract The total number of messages in the conversation, including user-generated messages.
 */
@property(readonly) NSUInteger messageCount;

/**
 *  @abstract Count of unread messages in the conversation.
 *
 *  @discussion The primary use of this property is to be able to display an indicator / badge when the conversation has unread messages.
 */
@property(readonly) NSUInteger unreadCount;

/**
 *  @abstract Date when the business last read the user messages
 */
@property(readonly) NSDate *appMakerLastRead;

/**
 *  @abstract Metadata associated with the conversation.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(readonly, nullable) NSDictionary* metadata;

/**
 *  @abstract A delegate object for receiving notifications related to the conversation.
 *
 *  @see SMMConversationDelegate
 */
@property(weak, nullable) id<SMMConversationDelegate> delegate;


/**
 *  @abstract Boolean representing whether there are previous messages in the conversation that can be fetched or not
 *
 *  @discussion Returns YES if there are previous messages in the conversation, NO otherwise. For fetching previous messages, use [SMMConversation loadPreviousMessages]
 */
@property(readonly) BOOL hasPreviousMessages;

/**
 *  @abstract Marks all unread messages as read.
 *
 *  @discussion Marks all unread messages as read, and notifies that the unread count changed.
 *
 *  @see SMMMessage
 */
-(void)markAllAsRead;

/**
 *  @abstract Loads previous messages for this conversation, if any
 *
 *  @discussion Will get previous messages for this conversation based on the timestamp of the current oldest message and will notify the delegate of new incoming messages through [SMMConversationDelegate conversation:didReceivePreviousMessages:]
 */
-(void)loadPreviousMessages;

/**
 *  @abstract Adds a new message to the conversation.
 *
 *  @discussion For each message added using `sendMessage`, a notification will be fired indicating the success or failure status of the upload.
 *
 *  @see SMMMessageUploadFailedNotification
 *  @see SMMMessageUploadCompletedNotification
 */
-(void)sendMessage:(SMMMessage*)message;

/**
 *  @abstract Adds an image message to the conversation.
 *
 *  @discussion Use the progress block to track the progress of the upload. Progress is reported as a number between 0 and 1.
 *
 *  The completion block is called when the operation completes, either in success or failure. Both blocks are guaranteed to be called on the main thread.
 *
 *  In case of success, the error parameter will be nil, and the message parameter will contain the newly created message. The message will already be part of the messages array when this block is called.
 *
 *  In case of failure, the message parameter will be nil, and the error parameter will contain the error that occurred.
 *
 *  @param image The image to upload. Must not be nil.
 *  @param progressBlock Called to report progress updates. May be nil.
 *  @param completionBlock Called when the upload completes or fails. May be nil.
 */
-(void)sendImage:(UIImage *)image withProgress:(nullable SMMImageUploadProgressBlock)progressBlock completion:(nullable SMMImageUploadCompletionBlock)completionBlock;

-(void)sendFile:(NSURL *)fileLocation withProgress:(nullable SMMFileUploadProgressBlock)progressBlock completion:(nullable SMMFileUploadCompletionBlock)completionBlock;

/**
 *  @abstract Sends a postback to the server.
 *
 *  @discussion The completion block is called when the operation completes, either in success or failure.
 *
 *  In case of success, the error parameter will be nil.
 *
 *  In case of failure, the error parameter will contain the error that occurred.
 *
 *  @param messageAction The messageAction for which to send the postback. Must not be nil.
 *  @param completionBlock Called when the postback completes or fails. May be nil.
 */
-(void)postback:(SMMMessageAction*)messageAction completion:(nullable void (^)(NSError* _Nullable error))completionBlock;

/**
 *  @abstract Retries a message that failed to send.
 *
 *  @discussion The failed message will be removed from the messages array, and a new message will be constructed with the same text as the failed message. A notification will be fired indicating the success or failure status of the upload.
 *
 *  @see SMMMessageUploadFailedNotification
 *  @see SMMMessageUploadCompletedNotification
 */
-(void)retryMessage:(SMMMessage*)failedMessage;

/**
 *  @abstract Notify the server that the user is typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  Typing updates are automatically throttled, so you may call this method as often as necessary. The typing stop event will automatically fire 10 seconds after the most recent call to this method.
 */
-(void)startTyping;

/**
 *  @abstract Notify the server that the user has finished typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  If the user was not flagged as typing recently, this method will result in a no-op.
 */
-(void)stopTyping;

@end

/**
 *  @discussion Delegate protocol for events related to the conversation.
 *
 *  Creating a delegate is optional, and may be used to receive callbacks when important changes happen in the conversation.
 *
 *  Delegate methods are guaranteed to be called from the main thread.
 */
@protocol SMMConversationDelegate <NSObject>

@optional
/**
 *  @abstract Notifies the delegate of a change in unread message count.
 *
 *  @discussion Called when conversation data is fetched from the server, or when the user enters the conversation screen.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param unreadCount The new number of unread messages.
 */
-(void)conversation:(SMMConversation*)conversation unreadCountDidChange:(NSUInteger)unreadCount;

/**
 *  @abstract Asks the delegate if an in-app notification should be shown for a message.
 *
 *  @discussion Called when a new message is received, right before the in-app notification is to be shown for that message. To show your own in-app notification, return NO from this method, and use the SMMMessage object to construct your view.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param message The message that will be displayed in the notification.
 *
 *  @return YES to allow Lithium to present the notification. NO to suppress the notification, and perform custom handling.
 *
 *  @see SMMMessage
 */
-(BOOL)conversation:(SMMConversation*)conversation shouldShowInAppNotificationForMessage:(SMMMessage*)message;

/**
 *  @abstract Asks the delegate if the conversation should show for the given action.
 *
 *  @discussion Called when the user performs an action that causes the conversation screen to show. Return NO to cancel the display of the conversation screen and perform your own handling of the action.
 *
 *  @param conversation The conversation object.
 *  @param action The action the user has taken.
 *  @param info An instance of NSDictionary with a `message` object with the latest SMMMessage represented as an NSDictionary
 *
 *  @return YES to allow default handling. NO to suppress the conversation screen, and perform custom handling.
 *
 *  @see SMMAction
 */
-(BOOL)conversation:(SMMConversation*)conversation shouldShowForAction:(SMMAction)action withInfo:(nullable NSDictionary *) info;

/**
 *  @abstract Gives the delegate the option to modify a message before it is sent
 *
 *  @discussion Called when a message is about to be sent to give the delegate the option of modify or decorate its content (i.e. add metadata) before sending to Lithium. When the message type is `file` or `image`, only the message `metadata` may be updated. Other message properties such as `type` or `text` won't be considered.
 *
 *  @return the message to be sent
 */
-(SMMMessage *)conversation:(SMMConversation*)conversation willSendMessage:(SMMMessage *)message;

/**
 *  @abstract Gives the delegate the option to modify a message before it is displayed. If nil is returned the message will be hidden
 *
 *  @discussion Called when a message is about to be displayed to the user to give the delegate the option of modifying its content before display or hide it
 *
 *  @return the message to be displayed. If nil, the message won't get displayed
 */
-(nullable SMMMessage *)conversation:(SMMConversation*)conversation willDisplayMessage:(SMMMessage *)message;

/**
 *  @abstract Notifies the delegate of new incoming messages.
 *
 *  @discussion Called when new messages are received from the server.
 *
 *  @param conversation The conversation object.
 *  @param messages An array of SMMMessage objects representing the new messages.
 *
 *  @see SMMMessage
 */
-(void)conversation:(SMMConversation*)conversation didReceiveMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate when older messages in the conversation history have been received
 *
 *  @discussion Called when older messages in the conversation history are received from the server
 *
 *  @param conversation The conversation object
 *  @param messages The messages that have been fetched
 */
-(void)conversation:(SMMConversation*)conversation didReceivePreviousMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate of new conversation activity
 *
 *  @discussion Called when a new activity is received from the server
 *
 *  @param conversation The conversation object
 *  @param activity The activity that was received
 */
-(void)conversation:(SMMConversation *)conversation didReceiveActivity:(SMMConversationActivity *)activity;

/**
 *  @abstract Asks the delegate if default handling should be performed for a message action.
 *
 *  @discussion Called when the user taps a message action.
 *
 *  @return YES to allow default handling. NO to perform custom handling.
 */
-(BOOL)conversation:(SMMConversation *)conversation shouldHandleMessageAction:(SMMMessageAction*)action;

/**
 *  @abstract Notifies the delegate when the conversation is about to be presented.
 *
 *  @discussion Called in the viewWillAppear: method of the conversation view controller.
 */
-(void)conversation:(SMMConversation *)conversation willShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when presentation of the conversation completes.
 *
 *  @discussion Called in the viewDidAppear: method of the conversation view controller.
 */
-(void)conversation:(SMMConversation *)conversation didShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when the conversation is about to be dismissed.
 *
 *  @discussion Called in the viewWillDisappear: method of the conversation view controller.
 */
-(void)conversation:(SMMConversation *)conversation willDismissViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when dismissal of the conversation completes.
 *
 *  @discussion Called in the viewDidDisappear: method of the conversation view controller.
 */
-(void)conversation:(SMMConversation *)conversation didDismissViewController:(UIViewController*)viewController;

@end
NS_ASSUME_NONNULL_END
