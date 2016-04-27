/*global cordova, module*/

var inputTriggerCallback    = null;
var outputTriggerCallback   = null;
var positionChangeCallback  = null;
var floorChangedCallback    = null;
var errorCallback           = null;

module.exports = {
    setToken: function (authToken, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "ProximiioCordova", "setToken", [authToken]);
    },

    setDebugOutput: function(enableDebug, successCallback, errorCallback)
    {
        cordova.exec(successCallback, errorCallback, "ProximiioCordova", "enableDebug", [(enableDebug || enableDebug > 0) ? "true" : "false"]);
    },

    setInputTriggerCallback: function(callback)
    {
        inputTriggerCallback = callback;
    },
    setOutputTriggerCallback: function(callback)
    {
        outputTriggerCallback = callback;
    },
    setPositionChangeCallback: function(callback)
    {
        positionChangeCallback = callback;
    },
    setFloorChangedCallback: function(callback)
    {
        floorChangedCallback = callback;
    },
    setErrorCallback: function(callback)
    {
        errorCallback = callback;
    },

    displayPushOutputMessage: function(pushOutput, successCallback, errorCallback)
    {
        cordova.exec(successCallback, errorCallback, "ProximiioCordova", "showPushMessage", [pushOutput.id]);
    },

    setRunOnBackground: function(run, successCallback, errorCallback)
    {
        cordova.exec(successCallback, errorCallback, "ProximiioCordova", "setRunOnBackground", [run]);
    },

    /* Called by native side */
    triggeredInput: function(enter, geofence) {
        var inputObj = eval(geofence);
        inputTriggerCallback(enter, geofence);
    },
    triggeredOutput: function(output) {
        console.log('should updateOutput:', output);
        var outputObj = eval(output);
        outputTriggerCallback(outputObj);
    },
    updatedPosition: function(coords) {
        console.log('should updatePosition:', coords);
        var coordsObj = eval(coords);
        positionChangeCallback(coords);
    },
    changedFloor: function(floor) {
        console.log('should change floor:', floor);
        var floorObj = eval(floor); 
        changedFloorCallback(floorObj);
    },
    encounteredError: function(code, id, str) {
        var errorObj = {};
        errorObj.domain = id;
        errorObj.code = code;
        errorObj.text = str;
        errorCallback(errorObj);
    }
};
