//
//  ProximiioDepartment.h
//  Proximiio
//
//  Created by Marian Frische on 27.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ProximiioCoordinates.h"


/*!
 @interface ProximiioDepartment
 @brief ProximiioDepartment interface.
 */
@interface ProximiioDepartment : NSObject

/*!
 @brief The unique department ID.
 */
@property (nonatomic, readonly) NSString *ID;
/*!
 @brief The readable name of this department.
 */
@property (nonatomic, readonly) NSString *name;
/*!
 @brief The ID of the place that is associated with this department.
 */
@property (nonatomic, readonly) NSString *placeID;
/*!
 @brief An array of tags that is assigned to this department.
 */
@property (nonatomic, readonly) NSArray  *tags;

/*!
 @brief Determines if a coordinate is within the polygonal region of this department.
 
 @param coordinates 
 The coordinates to be tested for.
 
 @return Returns wether the coordinates are within the department.
 */
- (BOOL)containsCoordinates:(ProximiioCoordinates*)coordinates;

@end
