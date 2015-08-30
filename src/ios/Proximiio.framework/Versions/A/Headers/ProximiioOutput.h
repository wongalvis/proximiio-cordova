//
//  ProximiioOutput.h
//  Proximiio
//
//  Created by Marian Frische on 23.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
 @interface ProximiioOutput
 @brief ProximiioOutput base interface.
 */
@interface ProximiioOutput : NSObject

/*!
 @brief The unique ID of this input.
 */
@property (nonatomic, readonly) NSString *ID;


/*!
 @brief Inits a @c ProximiioOutput instance.
 
 @param ID
 Unique Input ID.
 
 @return An initialized @c ProximiioOutput instance.
 */
- (ProximiioOutput*)initWithID:(NSString*)ID;

@end
