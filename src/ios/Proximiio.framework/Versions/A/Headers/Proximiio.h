//
//  Proximiio.h
//  Proximiio
//
//  Created by Marian Frische on 14.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProximiioSettings.h"

#import "ProximiioIBeaconInput.h"
#import "ProximiioGeofenceInput.h"
#import "ProximiioIndoorAtlasInput.h"
#import "ProximiioEddystoneInput.h"

#import "ProximiioRawOutput.h"
#import "ProximiioPushOutput.h"
#import "ProximiioXHTMLOutput.h"


@class Proximiio;
@class ProximiioActionFlow;

/*!
 * @typedef ProximiioUpdateType
 * @brief The different position update types that exist.
 * @constant kIBeaconPositionUpdate     Update through finding or updating the proximity of a beacon.
 * @constant kIndoorAtlasPositionUpdate Update through IndoorAtlas.
 * @constant kGeofencePositionUpdate    Update through entering/exiting a geofence.
 * @constant kSteerpathPositionUpdate   Update through SteerPath.
 * @constant kEddystonePositionUpdate   Update through Eddystone.
 */
typedef NS_ENUM(NSInteger, ProximiioUpdateType) {
    kIBeaconPositionUpdate,
    kIndoorAtlasPositionUpdate,
    kGeofencePositionUpdate,
    kSteerpathPositionUpdate,
    kEddystonePositionUpdate
};


/* Delegate events for the library user */
/*!
 @protocol ProximiioDelegate
 @brief Delegate for all direct Proximiio user interaction.
 */
@protocol ProximiioDelegate

/*!
 @brief Delegate that will be called whenever an input is triggered through being entered or exited.
 
 @param proximiio
 The Proximiio instance that triggered the input.
 @param input
 The input that got triggered.
 @param enter
 YES is the input got entered, NO if it got exited.
 */
- (void)proximiio:(Proximiio*)proximiio triggeredInput:(ProximiioInput*)input entered:(BOOL)enter;

/*!
 @brief Delegate that will be called for all the outputs attached to an input that has been triggered.
 
 @param proximiio
 The Proximiio instance that triggered the input.
 @param output
 The output that got triggered through the input.
 @param input
 The input that got triggered.
 @param actionFlow
 The action flow through which the output got attached to the input.
 */
- (void)proximiio:(Proximiio *)proximiio triggeredOutput:(ProximiioOutput *)output forInput:(ProximiioInput*)input inActionFlow:(ProximiioActionFlow*)actionFlow;

/*!
 @brief Delegate that will be called whenever the user position has been updated through an input.
 
 @param proximiio
 The Proximiio instance that triggered the input.
 @param coordinates
 The new user position in coordinates.
 @param updateType
 The input type that triggered the update.
 */
- (void)proximiio:(Proximiio *)proximiio updatedPositionToCoordinates:(ProximiioCoordinates*)coordinates byInputType:(ProximiioUpdateType)updateType;

/*!
 @brief Delegate that will be called, when there has been an error in the Proximiio library.
 
 @param proximiio
 The proximiio instance that triggered the input.
 @param error
 The error that occured.
 */
- (void)proximiio:(Proximiio *)proximiio encounteredError:(NSError*)error;

@end

/*!
 @interface Proximiio
 @brief Main interface for the Proximiio library.
 */
@interface Proximiio : NSObject


/*!
 @brief The user delegate.
 */
@property (nonatomic, weak)     id          delegate;

/*!
 @brief BOOL that states if the library is in debug mode, which means console debug log.
 */
@property (nonatomic, assign)   BOOL        debug;

/*!
 @brief Proximiio Application ID
 @see Proximi.io web portal to create a new application ID.
 */
@property (nonatomic, readonly) NSString    *appID;

/*!
 @brief A personalized ID generated for each device used to identify the user in the firebase.
 */
@property (nonatomic, readonly) NSString    *firebaseID;

/*!
 @brief The organization ID specified in the proximiio application settings.
 */
@property (nonatomic, readonly) NSString    *organizationID;

/*!
 @brief The proximiio application settings.
 @see proximi.io web portal to change the settings.
 */
@property (nonatomic, readonly) ProximiioSettings *settings;


/*!
 @brief Dictionary of all web portal defined action flows.
 @note The keys for this dictionary are the firebase IDs of those action flows.
 */
@property (nonatomic, readonly) NSDictionary *actionFlows;

/*!
 @brief Dictionary of all web portal defined inputs.
 @note The keys for this dictionary are the firebase IDs of those inputs.
 */
@property (nonatomic, readonly) NSDictionary *inputs;

/*!
 @brief Dictionary of all web portal defined outputs.
 @note The keys for this dictionary are the firebase IDs of those outputs.
 */
@property (nonatomic, readonly) NSDictionary *outputs;

/*!
 @brief Dictionary of all web portal defined departments.
 @note The keys for this dictionary are the firebase IDs of those departments.
 */
@property (nonatomic, readonly) NSDictionary *departments;

/*!
 @brief Dictionary of all web portal defined places.
 @note The keys for this dictionary are the firebase IDs of those places.
 */
@property (nonatomic, readonly) NSDictionary *places;

/*!
 @brief Dictionary of all web portal defined floors.
 @note The keys for this dictionary are the firebase IDs of those floors.
 */
@property (nonatomic, readonly) NSDictionary *floors;

/*!
 @brief Returns the proximiio singleton.
 @return The Proximiio singleton.
 */
+ (Proximiio*)sharedInstance;

/*!
 @brief Initialize or change the proximiio with your application ID and authentication token.
 
 @param appID
 Your application ID.
 @param authToken
 Your organizations authentication token.
 */
- (void)setAppID:(NSString *)appID andAuthToken:(NSString*)authToken;

- (void)setAppID:(NSString *)appID andAuthToken:(NSString*)authToken useDevelopmentFirebase:(BOOL)development;

@end
