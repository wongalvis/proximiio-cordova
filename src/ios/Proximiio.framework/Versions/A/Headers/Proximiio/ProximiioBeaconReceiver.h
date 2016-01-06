//
//  ProximiioBeaconReceiver.h
//  ProximiiBeaconLibrary
//
//  Created by Marian Frische on 06.09.14.
//  Copyright (c) 2014 Navture Apps. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "ProximiioBeacon.h"

@class ProximiioBeaconReceiver;

/* Delegate events for the library user */
/*!
 @protocol ProximiioBeaconReceiverDelegate
 @brief Delegate for the ProximiioBeaconReceiver
 
 Notifies the user about found, lost and updated iBeacons.
 */
@protocol ProximiioBeaconReceiverDelegate

/*!
 @brief Delegate that will be called whenever a new beacon has been found.
 
 @param receiver
 The ProximiioBeaconReceiver instance that found the @c beacon.
 @param beacon
 The ProximiioBeacon that got found.
 */
- (void)proximiioBeaconReceiver:(ProximiioBeaconReceiver*)receiver foundIBeacon:(ProximiioBeacon*)beacon;

/*!
 @brief Delegate that will be called whenever a beacon has been lost.
 
 @param receiver
 The ProximiioBeaconReceiver instance that found the @c beacon.
 @param beacon
 The ProximiioBeacon that was lost.
 */
- (void)proximiioBeaconReceiver:(ProximiioBeaconReceiver*)receiver lostIBeacon:(ProximiioBeacon*)beacon;

/*!
 @brief Delegate that will be called whenever a beacon proximity has been updated.
 
 @param receiver
 The ProximiioBeaconReceiver instance that found the @c beacon.
 @param beacon
 The ProximiioBeacon that changed proximty.
 */
- (void)proximiioBeaconReceiver:(ProximiioBeaconReceiver*)receiver updatedBeacon:(ProximiioBeacon*)beacon;

/*!
 @brief Delegate that will be called when there has been an error in the underlying CLLocationManager.
 
 @param receiver
 The ProximiioBeaconReceiver instance that found the beacon.
 @param error
 The error that occured.
 */
- (void)proximiioBeaconReceiver:(ProximiioBeaconReceiver *)receiver didFailWithError:(NSError*)error;

@end


/*  Class Interface */
/*!
 @interface ProximiioBeaconReceiver
 @brief ProximiioBeaconReceiver interface.
 */
@interface ProximiioBeaconReceiver : NSObject

/*!
 @brief The user delegate.
 */
@property (nonatomic, weak)     id      delegate;

/*!
 @brief BOOL that states whether the receiver is currently listening for beacons.
 */
@property (nonatomic, readonly) BOOL    isActive;

/*!
 @brief An array containing all beacon UUIDs/regions that are currently are being listened for.
 */
@property (nonatomic, readonly) NSArray *beaconRegions;


/*!
 @brief Adds a UUID scan region to the beacon listener.
 
 @param uuid
 The @c NSUUID to be listened for.
 @param identifier
 An identifier that can will be available in functions of the @c CLLocationManagerDelegate.
 */
- (void)addUUIDScanRegion:(NSUUID*)uuid regionIdentifier:(NSString*)identifier;

/*!
 @brief Stops the scan for all regions.
 */
- (void)stopScan;

@end
