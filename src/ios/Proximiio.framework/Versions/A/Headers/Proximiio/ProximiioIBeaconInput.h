//
//  ProximiioIBeaconInput.h
//  Proximiio
//
//  Created by Marian Frische on 22.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioInput.h"
#import "ProximiioBeacon.h"


/*!
 @interface ProximiioIBeaconInput
 @brief ProximiioIBeaconInput interface.
 */
@interface ProximiioIBeaconInput : ProximiioInput

/*!
 @brief The @c ProximiioBeacon that defines the trigger for this input.
 */
@property (nonatomic, readonly) ProximiioBeacon *beacon;


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
 @param beacon
 The beacon that will trigger this input.
 
 @return An initialized @c ProximiioIBeaconInput instance.
 */
- (ProximiioIBeaconInput*)initWithID:(NSString*)ID name:(NSString*)name coordinates:(ProximiioCoordinates*)coordinates departmentUID:(NSString*)departmentUID floorUID:(NSString*)floorUID placeUID:(NSString*)placeUID beacon:(ProximiioBeacon*)beacon;

@end
