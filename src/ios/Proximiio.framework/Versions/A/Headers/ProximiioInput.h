//
//  ProximiioInput.h
//  Proximiio
//
//  Created by Marian Frische on 22.04.15.
//  Copyright (c) 2015 NavtureApps. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProximiioCoordinates.h"
#import "ProximiioDepartment.h"

/*!
 @interface ProximiioInput
 @brief ProximiioInput base interface.
 */
@interface ProximiioInput : NSObject

/*!
 @brief The unique ID of this input.
 */
@property (nonatomic, readonly) NSString                *ID;
/*!
 @brief The user defined name of this input.
 */
@property (nonatomic, readonly) NSString                *name;
/*!
 @brief The currency based on the last input update.
 */
@property (nonatomic, readonly) double                  accuracy;
/*!
 @brief The coordinates of this input.
 */
@property (nonatomic, readonly) ProximiioCoordinates    *coordinates;
/*!
 @brief The ID of the department this input belongs to.
 */
@property (nonatomic, readonly) NSString                *departmentUID;
/*!
 @brief Boolean value that states whether the user is currently within the input area.
 */
@property (nonatomic, readonly) BOOL                    entered;
/*!
 @brief The unique ID of the visitor of this input.
 */
@property (nonatomic, readonly) NSString                *visitorID;
/*!
 @brief The department this input is associated with.
 */
@property (nonatomic, readonly) ProximiioDepartment     *department;
/*!
 @brief Determines if the input triggers a floor change
 */
@property (nonatomic, readonly) BOOL                    triggersFloorChange;
/*!
 @brief Floor to be changed to, in case this input triggers a floor change.
 */
@property (nonatomic, readonly) NSString*               floorUID;
/*!
 @brief Determines if the input triggers a place/venue change
 */
@property (nonatomic, readonly) BOOL                    triggersPlaceChange;
/*!
 @brief Place (venue) to be changed to, in case this input triggers a place change.
 */
@property (nonatomic, readonly) NSString*               placeIUD;


/*!
 @brief Inits a @c ProximiioInput instance.
 
 @param idString
 Unique Input ID.
 @param name
 User defined name.
 @param coordinates
 The coordinates of this input.
 @param departmentUID
 ID of the department this input belongs to.
 
 @return An initialized @c ProximiioInput instance.
 */
- (ProximiioInput*)initWithID:(NSString*)idString andName:(NSString*)name andCoordinates:(ProximiioCoordinates*)coordinates andDepartmentUID:(NSString*)departmentUID floorUID:(NSString*)floorUID placeUID:(NSString*)placeUID;

/*!
 @brief Returns the type string of this input.
 */
- (NSString*)typeString;

@end
