//
//  ProximiioGeofence.h
//  Proximiio
//
//  Created by Marian Frische on 28.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProximiioCoordinates.h"

/*!
 @interface ProximiioGeofence
 @brief ProximiioGeofence interface.
 */
@interface ProximiioGeofence : NSObject

/*!
 @brief Geofence ID based on the @c ProximiioInput that defines the geofence.
 */
@property (nonatomic, readonly) NSString                *ID;
/*!
 @brief Geofence name based on the @c ProximiioInput that defines the geofence.
 */
@property (nonatomic, readonly) NSString                *name;
/*!
 @brief @c ProximiioCoordinates definining the center and radius of the circular geofence.
 */
@property (nonatomic, readonly) ProximiioCoordinates    *coordinates;

/*!
 @brief BOOL stating whether the user is currently within the geofence.
 @warning This value is only true when Geofences are currently enabled. Otherwise it might be out of date.
 */
@property (nonatomic, readonly) BOOL                    insideGeofence;

@end
