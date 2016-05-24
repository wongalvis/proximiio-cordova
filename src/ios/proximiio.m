/********* proximiio.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

#import <Proximiio/Proximiio.h>

@interface proximiio : CDVPlugin <ProximiioDelegate> {
  // Member variables go here.
}

- (void)setToken:(CDVInvokedUrlCommand*)command;
- (void)showPushMessage:(CDVInvokedUrlCommand*)command;

@end

@implementation proximiio

- (void)setToken:(CDVInvokedUrlCommand*)command
{
    NSString* callbackId    = [command callbackId];
    NSString* authToken     = [[command arguments] objectAtIndex:0];

    [[self commandDelegate] runInBackground:^{
        [[Proximiio sharedInstance] setDelegate:self];
        [[Proximiio sharedInstance] authWithToken:authToken];
        
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
    }];
}

- (void)enableDebug:(CDVInvokedUrlCommand*)command
{
    NSString* callbackId    = [command callbackId];
    NSString* enableString  = [[command arguments] objectAtIndex:0];

//    if([enableString isEqualToString:@"true"])
//        [[Proximiio sharedInstance] setDebug:YES];
//    else
//        [[Proximiio sharedInstance] setDebug:NO];

    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
}

- (void)showPushMessage:(CDVInvokedUrlCommand*)command
{
    NSString* callbackId    = [command callbackId];
    NSString* idStr         = [[command arguments] objectAtIndex:0];

    CDVPluginResult* result;

    if(idStr != nil)
    {
          result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
//        ProximiioPushOutput *pushOutput = (ProximiioPushOutput*)[[[Proximiio sharedInstance] outputs] objectForKey:idStr];
//        if([pushOutput respondsToSelector:@selector(display)])
//        {
//            [pushOutput display];
//            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
//        }
//        else
//            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    else
        result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
}

- (NSString*)beaconToString:(ProximiioBeacon*)beacon
{
    return [NSString stringWithFormat:@"{uuid:'%@', major:%d, minor:%d, accuracy:%f}",
        [[beacon uuid] UUIDString], [beacon major], [beacon minor], [beacon distance]];
}

- (NSString*)eddystoneToString:(ProximiioEddystoneBeacon*)beacon
{
    return [NSString stringWithFormat:@"{namespace:'%@', instanceID:'%@', url:'%@', batteryVoltage:%.2f, temperature:%.2f, uptime:%d, pdu:%d}",
        [beacon Namespace], [beacon InstanceID], [beacon URL], [[beacon batteryVoltage] floatValue], [[beacon temperature] floatValue], [[beacon uptime] intValue], [[beacon PDU] intValue]];
}

- (BOOL)proximiioHandlePushMessage:(NSString*)title
{
    NSLog(@"handle push: %@", title);
    [self runJavascript:[NSString stringWithFormat:@"proximiio.pushMessage(\"%@\");", title]];
    return YES;
}

- (void)proximiioHandleOutput:(NSObject*)payload
{
    NSLog(@"handle output: %@", payload);
    [self runJavascript:[NSString stringWithFormat:@"proximiio.triggeredOutput(%@);", payload]];
}

- (void)proximiioEnteredGeofence:(ProximiioGeofence*)geofence
{
    NSLog(@"entered geofence: %@", geofence);
    [self runJavascript:[NSString stringWithFormat:@"proximiio.triggeredInput(1, %@);", geofence.json]];
}

- (void)proximiioExitedGeofence:(ProximiioGeofence*)geofence
{
    NSLog(@"exited geofence: %@", geofence);
    [self runJavascript:[NSString stringWithFormat:@"proximiio.triggeredInput(0, %@);", geofence.json]];
}

- (void)proximiioPositionUpdated:(CLLocation *)location
{
    NSLog(@"positions updated");
    NSString *coordinates = [NSString stringWithFormat:@"{\"accuracy\": %1.8f, \"coordinates\": {\"lat\": %1.8f, \"lon\": %1.8f}}", location.horizontalAccuracy, location.coordinate.latitude, location.coordinate.longitude];
    NSString *jsString = [NSString stringWithFormat:@"proximiio.updatedPosition(%@);", coordinates];
    [self runJavascript:jsString];
}

- (void)proximiio:(Proximiio *)proximiio encounteredError:(NSError*)error
{
    NSString* jsString = [NSString stringWithFormat:@"proximiio.encounteredError(%ld, \"%@\", \"%@\");", (long)error.code, error.domain, error.localizedDescription];
    [self runJavascript:jsString];
}


- (void)runJavascript:(NSString *)command
{
    NSLog(@"!!! runJavascript: %@", command);
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:command waitUntilDone:NO];
}

@end

