//
//  ProximiioGeofenceReceiver.h
//  Proximiio
//
//  Created by Marian Frische on 28.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProximiioGeofence.h"
#import <CoreLocation/CoreLocation.h>


@class ProximiioGeofenceReceiver;

/* Delegate events for the library user */
/*!
 @protocol ProximiioGeofenceReceiverDelegate
 @brief Delegate for the ProximiioGeofenceReceiverDelegate
 
 Notifies the user about entered and exited geofences.
 */
@protocol ProximiioGeofenceReceiverDelegate

/*!
 @brief Delegate that will be called when the geofence has been entered.
 @note Will also be called, when the geofence is first registered and we are already inside.
 
 @param geofenceReceiver
 The ProximiioGeofenceReceiver instance that determined the entry of the @c geofence.
 @param geofence
 The ProximiioGeofence that has been entered.
 */
- (void)proximiioGeofenceReceiver:(ProximiioGeofenceReceiver*)geofenceReceiver enteredGeofence:(ProximiioGeofence*)geofence;

/*!
 @brief Delegate that will be called when the geofence has been exited.
 
 @param geofenceReceiver
 The ProximiioGeofenceReceiver instance that determined the entry of the @c geofence.
 @param geofence
 The ProximiioGeofence that has been exited.
 */
- (void)proximiioGeofenceReceiver:(ProximiioGeofenceReceiver*)geofenceReceiver exitedGeofence:(ProximiioGeofence*)geofence;

/*!
 @brief Delegate that will be called when there has been an error in the underlying CLLocationManager.
 
 @param geofenceReceiver
 The ProximiioGeofenceReceiver instance that determined the entry of the @c geofence.
 @param error
 The error that occured.
 */
- (void)proximiioGeofenceReceiver:(ProximiioGeofenceReceiver*)geofenceReceiver didFailWithError:(NSError*)error;


@end


/*!
 @interface ProximiioGeofenceReceiver
 @brief ProximiioGeofenceReceiver interface.
 */
@interface ProximiioGeofenceReceiver : NSObject

/*!
 @brief The user delegate.
 */
@property (nonatomic, weak)   id   delegate;

/*!
 @brief A boolean value that determines whether the @c ProximiioGeofenceReceiver is enabled.
 */
@property (nonatomic, assign) BOOL enabled;


/*!
 @brief Adds a geofence to be observered by this instance of the @c ProximiioGeofenceReceiver.
 
 @param geofence
 The geofence that will be observed.
 */
- (void)addGeofence:(ProximiioGeofence*)geofence;

/*!
 @brief Removes all geofences from the receiver.
 */
- (void)removeAllGeofences;

@end
