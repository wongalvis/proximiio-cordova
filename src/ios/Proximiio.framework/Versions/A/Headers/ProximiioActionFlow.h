//
//  ProximiioActionFlow.h
//  Proximiio
//
//  Created by Marian Frische on 22.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProximiioInput.h"


/*!
 @interface ProximiioActionFlow
 @brief ProximiioActionFlow interface.
 */
@interface ProximiioActionFlow : NSObject

/*!
 @brief The unique ID of this input.
 */
@property(nonatomic, readonly) NSString *ID;
/*!
 @brief The input that can trigger this action flow.
 */
@property (nonatomic, readonly) ProximiioInput  *input;
/*!
 @brief An array of outputs that will be triggered once the input gets triggered.
 */
@property (nonatomic, readonly) NSArray         *outputs;

@end
