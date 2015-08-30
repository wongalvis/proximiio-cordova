/*global cordova, module*/

var inputTriggerCallback    = null;
var outputTriggerCallback   = null;
var positionChangeCallback  = null;
var errorCallback           = null;

module.exports = {
    setIDandAuthToken: function (id, authToken, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "ProximiioCordova", "setIDandAuthToken", [id, authToken]);
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
    triggeredInput: function(entered, input) {
        var inputObj = eval(input);
        inputTriggerCallback(inputObj, entered);
    },
    triggeredOutput: function(output, input) {
        var inputObj = eval(input);
        var outputObj = eval(output);
        outputTriggerCallback(outputObj, inputObj);
    },
    updatedPosition: function(coords) {
        var coordsObj = eval(coords);
        positionChangeCallback(coordsObj);
    },
    encounteredError: function(code, id, str) {
        var errorObj = {};
        errorObj.domain = id;
        errorObj.code = code;
        errorObj.text = str;
        errorCallback(errorObj);
    }
};
