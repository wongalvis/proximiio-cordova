//
//  ProximiioIndoorAtlasInput.h
//  Proximiio
//
//  Created by Marian Frische on 29.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioInput.h"


/*!
 @interface ProximiioIndoorAtlasInput
 @brief ProximiioIndoorAtlasInput interface.
 */
@interface ProximiioIndoorAtlasInput : ProximiioInput

/*!
 @brief Tests whether a coordinate is within the input defined circular region.
 
 @param coordinate
 Coordinate to be tested.
 
 @return Returns whether the coordinate is within the defined radius or not.
 */
- (BOOL)containsCoordinate:(ProximiioCoordinates*)coordinate;

@end
