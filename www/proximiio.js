/*global cordova, module*/

var dummy = function (obj) {
  console.log('proximiio dummy:' + JSON.stringify(obj));
};

var inputTriggerCallback    = dummy;
var outputTriggerCallback   = dummy;
var positionChangeCallback  = dummy;
var floorChangedCallback    = dummy;
var errorCallback           = dummy;
var proximiioReadyCallback  = dummy;
var beaconFoundCallback     = dummy;
var beaconLostCallback      = dummy;

module.exports = {
  setToken: function (authToken, successCallback, errorCallback) {
    cordova.exec(successCallback, errorCallback, 'ProximiioCordova', 'setToken', [authToken]);
  },

  setDebugOutput: function (enableDebug, successCallback, errorCallback) {
    var enableDebug = [(enableDebug || enableDebug > 0) ? 'true' : 'false'];
    cordova.exec(successCallback, errorCallback, 'ProximiioCordova', 'enableDebug', enableDebug);
  },

  setInputTriggerCallback: function (callback) { inputTriggerCallback = callback; },

  setOutputTriggerCallback: function (callback) { outputTriggerCallback = callback; },

  setPositionChangeCallback: function (callback) { positionChangeCallback = callback; },

  setFloorChangedCallback: function (callback) { floorChangedCallback = callback; },

  setErrorCallback: function (callback) { errorCallback = callback; },

  setProximiioReadyCallback: function (callback) { proximiioReadyCallback = callback; },

  setBeaconFoundCallback: function (callback) { beaconFoundCallback = callback; },

  setBeaconLostCallback: function (callback) { beaconLostCallback = callback; },

  displayPushOutputMessage: function (pushOutput, successCallback, errorCallback) {
    cordova.exec(successCallback, errorCallback, 'ProximiioCordova', 'showPushMessage', [pushOutput.id]);
  },

  setRunOnBackground: function (run, successCallback, errorCallback) {
    cordova.exec(successCallback, errorCallback, 'ProximiioCordova', 'setRunOnBackground', [run]);
  },

  /* Called by native side */
  triggeredInput: function (enter, geofence) {
    inputTriggerCallback(enter, geofence);
  },

  triggeredOutput: function (output) {
    outputTriggerCallback(output);
  },

  updatedPosition: function (coords) {
    console.log('should updatePosition:' + coords);
    var coordsObj = eval(coords);
    positionChangeCallback(coords);
  },

  changedFloor: function (floor) { floorChangedCallback(eval(floor)); },

  proximiioReady: function (visitorId) { proximiioReadyCallback(visitorId); },

  foundBeacon: function (beacon) { beaconFoundCallback(eval(beacon)); },

  lostBeacon: function (beacon) { beaconLostCallback(eval(beacon)); },

  encounteredError: function (code, id, str) {
    var errorObj = {};
    errorObj.domain = id;
    errorObj.code = code;
    errorObj.text = str;
    errorCallback(errorObj);
  },

};
