/********* proximiio.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

#import <Proximiio/Proximiio.h>

@interface proximiio : CDVPlugin <ProximiioDelegate> {
  // Member variables go here.
  @property (readwrite, assign) BOOL enableDebug;
  @property (readwrite, assign) BOOL handlePush;
}

- (void)setToken:(CDVInvokedUrlCommand*)command;
- (void)enableDebug:(CDVInvokedUrlCommand*)command;
- (void)handlePush:(CDVInvokedUrlCommand*)command;

@end

@implementation proximiio

// ACTIONS

- (void)setToken:(CDVInvokedUrlCommand*)command {
    NSString* callbackId    = [command callbackId];
    NSString* authToken     = [[command arguments] objectAtIndex:0];

    [[self commandDelegate] runInBackground:^{
        [[Proximiio sharedInstance] setDelegate:self];
        [[Proximiio sharedInstance] authWithToken:authToken];

        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
    }];
}

- (void)enableDebug:(CDVInvokedUrlCommand*)command {
    NSString* callbackId    = [command callbackId];
    NSString* enableString  = [[command arguments] objectAtIndex:0];
    _enableDebug = [enableString isEqualToString:@"true"];
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
}

- (void)handlePush:(CDVInvokedUrlCommand*)command {
    NSString* callbackId    = [command callbackId];
    NSString* handleString  = [[command arguments] objectAtIndex:0];
    _handlePush = [handleString isEqualToString:@"true"];
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
}

// HELPERS

- (NSString*)beaconToString:(ProximiioBeacon*)beacon {
    return [NSString stringWithFormat:@"{uuid:'%@', major:%d, minor:%d, accuracy:%f}",
        [[beacon uuid] UUIDString], [beacon major], [beacon minor], [beacon distance]];
}

- (NSString*)eddystoneToString:(ProximiioEddystoneBeacon*)beacon {
    return [NSString stringWithFormat:@"{namespace:'%@', instanceID:'%@', url:'%@', batteryVoltage:%.2f, temperature:%.2f, uptime:%d, pdu:%d}",
        [beacon Namespace], [beacon InstanceID], [beacon URL], [[beacon batteryVoltage] floatValue], [[beacon temperature] floatValue], [[beacon uptime] intValue], [[beacon PDU] intValue]];
}

// PROXIMI.IO DELEGATES

- (BOOL)proximiioHandlePushMessage:(NSString*)title {
    if (_handlePush) {
      return YES;
    } else {
      NSString *action = [NSString stringWithFormat:@"proximiio.pushMessage(\"%@\");", title];
      [self log:@"proximiioHandlePushMessage" action:action];
      [self runJavascript:action];
      return NO;
    }
}

- (void)proximiioHandleOutput:(NSObject*)payload {
    NSString *action = [NSString stringWithFormat:@"proximiio.triggeredOutput(%@);", payload];
    [self log:@"proximiioHandleOutput" action:action];
    [self runJavascript:action];
}

- (void)proximiioEnteredGeofence:(ProximiioGeofence*)geofence {
    NSString *action = [NSString stringWithFormat:@"proximiio.triggeredInput(1, %@);", geofence.json];
    [self log:@"proximiioExitedGeofence" action:action];
    [self runJavascript:action];
}

- (void)proximiioExitedGeofence:(ProximiioGeofence*)geofence {
    NSString *action = [NSString stringWithFormat:@"proximiio.triggeredInput(0, %@);", geofence.json];
    [self log:@"proximiioExitedGeofence" action:action];
    [self runJavascript:action];
}

- (void)proximiioPositionUpdated:(CLLocation *)location {
    NSString *coordinates = [NSString stringWithFormat:@"{\"accuracy\": %1.8f, \"coordinates\": {\"lat\": %1.8f, \"lon\": %1.8f}}", location.horizontalAccuracy, location.coordinate.latitude, location.coordinate.longitude];
    NSString *action = [NSString stringWithFormat:@"proximiio.updatedPosition(%@);", coordinates];
    [self log:@"proximiioPositionUpdated" action:action];
    [self runJavascript:action];
}

- (void)proximiio:(Proximiio *)proximiio encounteredError:(NSError*)error {
    NSString *action = [NSString stringWithFormat:@"proximiio.encounteredError(%ld, \"%@\", \"%@\");", (long)error.code, error.domain, error.localizedDescription];
    [self log:@"proximiio:encounteredError" action:action];
    [self runJavascript:action];
}

- (void)log:(NSString *)method action:(NSString *)action {
    if (_enableDebug) {
      NSLog(@"[ProximiioSDK] %@: %@", method, action);
    }
}

- (void)runJavascript:(NSString *)command {
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:command waitUntilDone:NO];
}

@end
