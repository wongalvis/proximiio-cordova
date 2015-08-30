//
//  ProximiioCoordinates.h
//  Proximiio
//
//  Created by Marian Frische on 22.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
 @interface ProximiioCoordinates
 @brief ProximiioCoordinates interface.
 */
@interface ProximiioCoordinates : NSObject

/*!
 @brief The latitude angle.
 */
@property (nonatomic, readonly) double latitude;
/*!
 @brief The longitude angle.
 */
@property (nonatomic, readonly) double longitude;
/*!
 @brief The radius if this coordinate has some uncertainty or defines are circular area.
 */
@property (nonatomic, readonly) double radius;

/*!
 @brief Initializes a @c ProximiioCoordinates instance.
 
 @param latitude   
 North-south position in degrees.
 @param longitude
 East-west position in degrees.
 @param radius
 Uncertainty or radius. If not required leave zero.
 
 @return Returns an initialized instance of the ProximiioCoordinates.
 */
- (ProximiioCoordinates*)initWithLatitude:(double)latitude longitude:(double)longitude radius:(double)radius;

/*!
 @brief Distance from this to another set of coordinates.
 
 @param coordinates
 The set of coordinates from which the distance should be calculated.
 
 @return Returns the distance between the two coordinates in meters.
 */
- (double)distanceToCoordinates:(ProximiioCoordinates*)coordinates;

@end
