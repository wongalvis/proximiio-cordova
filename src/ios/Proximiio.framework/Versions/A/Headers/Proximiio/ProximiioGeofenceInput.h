//
//  ProximiioGeofenceInput.h
//  Proximiio
//
//  Created by Marian Frische on 28.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioInput.h"
#import "ProximiioGeofence.h"


/*!
 @interface ProximiioGeofenceInput
 @brief ProximiioGeofenceInput interface.
 */
@interface ProximiioGeofenceInput : ProximiioInput

/*!
 @brief The @c ProximiioGeofence that will trigger this input.
 */
@property (nonatomic, readonly) ProximiioGeofence *geofence;

/*!
 @brief Inits a @c ProximiioIBeaconInput instance.
 
 @param ID
 Unique Input ID.
 @param name
 User defined name.
 @param coordinates
 The coordinates of this input.
 @param departmentUID
 ID of the department this input belongs to.
 @param geofence
 The geofence that will trigger this input.
 
 @return An initialized @c ProximiioIBeaconInput instance.
 */
- (ProximiioGeofenceInput*)initWithID:(NSString*)ID name:(NSString*)name coordinates:(ProximiioCoordinates*)coordinates departmentUID:(NSString*)departmentUID floorUID:(NSString*)floorUID placeUID:(NSString*)placeUID geofence:(ProximiioGeofence*)geofence;

@end
