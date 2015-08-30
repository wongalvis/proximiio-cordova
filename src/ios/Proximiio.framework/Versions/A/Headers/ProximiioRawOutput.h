//
//  ProximiioRawOutput.h
//  Proximiio
//
//  Created by Marian Frische on 28.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioOutput.h"

/*!
 @interface ProximiioRawOutput
 @brief Dummy class until there is further input in the web portal.
 */
@interface ProximiioRawOutput : ProximiioOutput

/*!
 @brief Dictionary containing all keys and values configured in the portal.
 */
@property (nonatomic, readonly) NSDictionary *pairs;


/*!
 @brief Inits a ProximiioRawOutput instance.
 
 @param ID
 Unique Input ID.
 @param pairs
 The dictionary containing the key-value pairs.
 
 @return An initialized ProximiioRawOutput instance.
 */
- (ProximiioRawOutput*)initWithID:(NSString*)ID pairs:(NSDictionary*)pairs;


@end
