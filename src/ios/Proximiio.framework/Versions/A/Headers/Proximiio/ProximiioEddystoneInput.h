//
//  ProximiioEddystoneInput.h
//  Proximiio
//
//  Created by Marian Frische on 02.08.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import "ProximiioInput.h"
#import "ProximiioEddystoneBeacon.h"

@interface ProximiioEddystoneInput : ProximiioInput

@property (nonatomic, readonly) NSString *Namespace;
@property (nonatomic, readonly) NSString *InstanceID;


- (ProximiioEddystoneInput*)initWithID:(NSString*)ID name:(NSString*)name coordinates:(ProximiioCoordinates*)coordinates departmentUID:(NSString*)departmentUID floorUID:(NSString*)floorUID placeUID:(NSString*)placeUID namespace:(NSString*)Namespace instanceID:(NSString*)instanceID;

- (ProximiioEddystoneBeacon*)lastTriggerBeacon;

@end
