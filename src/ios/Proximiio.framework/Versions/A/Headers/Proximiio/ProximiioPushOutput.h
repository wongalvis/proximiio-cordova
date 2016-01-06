//
//  ProximiioPushOutput.h
//  Proximiio
//
//  Created by Marian Frische on 28.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioOutput.h"


/*!
 @interface ProximiioPushOutput
 @brief ProximiioPushOutput interface.
 */
@interface ProximiioPushOutput : ProximiioOutput

/*!
 @brief Title string of the push message.
 */
@property (nonatomic, readonly) NSString *title;
/*!
 @brief Content string of the push message.
 */
@property (nonatomic, readonly) NSString *content;


/*!
 @brief Inits a @c ProximiioPushOutput instance.
 
 @param ID
 Unique Input ID.
 @param title
 Push title string.
 @param content
 Push message content string.
 
 @return An initialized @c ProximiioPushOutput instance.
 */
- (ProximiioPushOutput*)initWithID:(NSString*)ID title:(NSString*)title andContent:(NSString*)content;

/*!
 @brief Displays the notification.
 */
- (void)display;

@end
