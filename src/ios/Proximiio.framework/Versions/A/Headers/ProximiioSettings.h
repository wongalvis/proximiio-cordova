//
//  ProximiioSettings.h
//  Proximiio
//
//  Created by Marian Frische on 15.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @interface ProximiioSettings
 @brief Settings interface.
 */
@interface ProximiioSettings : NSObject

/*!
 @brief BOOL that states whether GPS Geofences are enabled.
 */
@property (nonatomic, readonly) BOOL        GPSGeofences;

/*!
 @brief BOOL that states whether iBeacons are enabled.
 */
@property (nonatomic, readonly) BOOL        iBeacons;
/*!
 @brief String with the iBeacon UUID that is being listened for.
 */
@property (nonatomic, readonly) NSString    *iBeaconUUIDRange;

/*!
 @brief BOOL that states whether the IndoorAtlas is enabled.
 */
@property (nonatomic, readonly) BOOL        IndoorAtlas;
/*!
 @brief IndoorAtlas API Key that is used for authentication.
 */
@property (nonatomic, readonly) NSString    *IndoorAtlasAPIKey;
/*!
 @brief IndoorAtlas API Secret that is used for authentication.
 */
@property (nonatomic, readonly) NSString    *IndoorAtlasAPIKeySecret;
/*!
 @brief IndoorAtlas floor ID
 @note Currently unused in the library.
 */
@property (nonatomic, readonly) NSString    *IndoorAtlasFloorID;
/*!
 @brief IndoorAtlas floorplan ID that is used to get the floorplan for postioning.
 */
@property (nonatomic, readonly) NSString    *IndoorAtlasFloorPlanID;
/*!
 @brief IndoorAtlas venue ID
 @note Currently unused in the library.
 */
@property (nonatomic, readonly) NSString    *IndoorAtlasVenueID;

/*!
 @brief BOOL that states whether Steerpaths are enabled.
 */
@property (nonatomic, readonly) BOOL        Steerpath;
/*!
 @brief IndoorAtlas floorplan ID that is used to get the floorplan for postioning.
 */
@property (nonatomic, readonly) NSString    *SteerpathNDD;

/*!
 @brief BOOL that changes state whenever the settings are updated.
 @warning The state of the BOOL does @b not state if the settings have changed (recently). It should only be used in key-value observations.
 */
@property (nonatomic, readonly) BOOL        changed;

@end
