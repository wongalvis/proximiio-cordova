/********* proximiio.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>

#import <Proximiio/Proximiio.h>

@interface proximiio : CDVPlugin {
  // Member variables go here.
}

- (void)setIDandAuthToken:(CDVInvokedUrlCommand*)command;

- (void)showPushMessage:(CDVInvokedUrlCommand*)command;

@end

@implementation proximiio

- (void)setIDandAuthToken:(CDVInvokedUrlCommand*)command
{
    NSString* callbackId    = [command callbackId];
    NSString* idStr         = [[command arguments] objectAtIndex:0];
    NSString* authToken     = [[command arguments] objectAtIndex:1];

    [[self commandDelegate] runInBackground:^{
        [[Proximiio sharedInstance] setAppID:idStr andAuthToken:authToken];
        [[Proximiio sharedInstance] setDelegate:self];
        
        CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        
        [[self commandDelegate] sendPluginResult:result callbackId:callbackId];
    }];
}

- (void)enableDebug:(CDVInvokedUrlCommand*)command
{
    NSString* callbackId    = [command callbackId];
    NSString* enableString  = [[command arguments] objectAtIndex:0];

    if([enableString isEqualToString:@"true"])
        [[Proximiio sharedInstance] setDebug:YES];
    else
        [[Proximiio sharedInstance] setDebug:NO];

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
        ProximiioPushOutput *pushOutput = (ProximiioPushOutput*)[[[Proximiio sharedInstance] outputs] objectForKey:idStr];
        if([pushOutput respondsToSelector:@selector(display)])
        {
            [pushOutput display];
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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

- (NSString*)inputToString:(ProximiioInput*)input
{
    NSString *typeString = @"Unknown";
    if([input class] == [ProximiioIBeaconInput class])
    {
        ProximiioIBeaconInput *beaconInput = (ProximiioIBeaconInput*)input;
        return [NSString stringWithFormat:@"\"({type:'iBeacon', id:'%@', name:'%@', accuracy:%f, coordinates:{lat:%f, lon:%f}, departmentid:'%@', entered:%d, beacon:%@})\"", [input ID], [input name], [input accuracy], [[input coordinates] latitude], [[input coordinates] longitude], [input departmentUID], [input entered] ? 1 : 0, [self beaconToString:[beaconInput beacon]]];
    }
    else if([input class] == [ProximiioEddystoneInput class])
    {
        ProximiioEddystoneInput *eddystoneInput = (ProximiioEddystoneInput*)input;
        return [NSString stringWithFormat:@"\"({type:'Eddystone', id:'%@', name:'%@', accuracy:0, coordinates:{lat:%f, lon:%f}, departmentid:'%@', entered:%d, beacon:%@})\"", [input ID], [input name], [[input coordinates] latitude], [[input coordinates] longitude], [input departmentUID], [input entered] ? 1 : 0, [self eddystoneToString:[eddystoneInput lastTriggerBeacon]]];
    }
    else if([input class] == [ProximiioGeofenceInput class])
        typeString = @"GPSGeofence";
    else if([input class] == [ProximiioIndoorAtlasInput class])
        typeString = @"IndoorAtlas";
    return [NSString stringWithFormat:@"\"({type:'%@', id:'%@', name:'%@', accuracy:%f, coordinates:{lat:%f, lon:%f}, departmentid:'%@', entered:%d})\"", typeString, [input ID], [input name], [input accuracy], [[input coordinates] latitude], [[input coordinates] longitude], [input departmentUID], [input entered] ? 1 : 0];
}

- (NSString*)outputToString:(ProximiioOutput*)output
{
    if([output class] == [ProximiioPushOutput class])
    {
        ProximiioPushOutput *pushOutput = (ProximiioPushOutput*)output;

        return [NSString stringWithFormat:@"\"({type:'PushMessage', id:'%@', title:'%@', content:'%@'})\"", [output ID], [[pushOutput title] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""], [[pushOutput content] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""]];
    }
    else if([output class] == [ProximiioRawOutput class])
    {
        return [NSString stringWithFormat:@"\"({type:'Raw', id:'%@'})\"", [output ID]];
    }
    else if([output class] == [ProximiioXHTMLOutput class])
    {
        ProximiioXHTMLOutput *xhtmlOutput = (ProximiioXHTMLOutput*)output;
        return [NSString stringWithFormat:@"\"({type:'XHTML', id:'%@', title:'%@', content:'%@'})\"", [output ID], [[xhtmlOutput title] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""], [[xhtmlOutput content] stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""]];
    }
    else
        return [NSString stringWithFormat:@"\"({type:'Unkown', id:'%@'})\"", [output ID]];
}

- (NSString*)coordinatesToString:(ProximiioCoordinates*)coordinates
{
        return [NSString stringWithFormat:@"\"({lat:%f, lon:%f})\"", [coordinates latitude], [coordinates longitude]];
}

/*
Delegate functions
*/
- (void)proximiio:(Proximiio *)proximiio triggeredOutput:(ProximiioOutput *)output forInput:(ProximiioInput *)input inActionFlow:(ProximiioActionFlow *)actionFlow
{
    NSString* jsString = [NSString stringWithFormat:@"proximiio.triggeredOutput(%@, %@);", [self outputToString:output], [self inputToString:input]];
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:jsString waitUntilDone:NO];
}

- (void)proximiio:(Proximiio*)proximiio triggeredInput:(ProximiioInput*)input entered:(BOOL)enter
{
    NSString* jsString = [NSString stringWithFormat:@"proximiio.triggeredInput(%d, %@);", enter ? 1 : 0, [self inputToString:input]];
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:jsString waitUntilDone:NO];
}

- (void)proximiio:(Proximiio *)proximiio updatedPositionToCoordinates:(ProximiioCoordinates*)coordinates byInputType:(ProximiioUpdateType)updateType;
{
    NSString* jsString = [NSString stringWithFormat:@"proximiio.updatedPosition(%@);", [self coordinatesToString:coordinates]];
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:jsString waitUntilDone:NO];
}

- (void)proximiio:(Proximiio *)proximiio encounteredError:(NSError*)error
{
    NSString* jsString = [NSString stringWithFormat:@"proximiio.encounteredError(%ld, \"%@\", \"%@\");", (long)error.code, error.domain, error.localizedDescription];
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject:jsString waitUntilDone:NO];
}

@end
