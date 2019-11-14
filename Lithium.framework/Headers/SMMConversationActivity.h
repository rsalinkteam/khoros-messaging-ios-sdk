//
//  SMMConversationActivity.h
//  Lithium
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract An activity type indicating that the appMaker started typing a response
 */
extern NSString const *SMMConversationActivityTypeTypingStart;

/**
 *  @abstract An activity type indicating that the appMaker stopped typing a response
 */
extern NSString const *SMMConversationActivityTypeTypingStop;

/**
 *  @abstract An activity type indicating that the appMaker recently read the user message
 */
extern NSString const *SMMConversationActivityTypeConversationRead;

/**
 *  @abstract A key whose value is an NSString representing the appMaker name.
 *
 *  @discussion This key is used in the SMMConversationActivity data object.
 */
extern NSString const *SMMConversationActivityDataNameKey;

/**
 *  @abstract A key whose value is an NSString representing the URL of the appMaker avatar.
 *
 *  @discussion This key is used in the SMMConversationActivity data object.
 */
extern NSString const *SMMConversationActivityDataAvatarUrlKey;

@interface SMMConversationActivity : NSObject

/**
 *  @abstract the role of who is performing the typing activity
 */
@property(readonly) NSString *role;

/**
 *  @abstract the type of activity that is being triggered. Could be either SMMConversationActivityTypeTypingStart, SMMConversationActivityTypeTypingStop or SMMConversationActivityTypeConversationRead
 */
@property(readonly) NSString *type;

/**
 *  @abstract additional data for this activity. Posible values are the appMaker's 'name' and/or 'avatarUrl'
 */
@property(readonly, nullable) NSDictionary *data;

/**
 *  @abstract date when the appMaker last read user messages for activities of type SMMConversationActivityTypeConversationRead
 */
@property(readonly, nullable) NSDate *appMakerLastRead;

@end
NS_ASSUME_NONNULL_END
