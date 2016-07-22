# Proximi.io Cordova Plugin #

### Installation / Cordova ###

```
cordova plugin add https://github.com/proximiio/proximiio-cordova.git
```

### Installation / IONIC ###


```
ionic plugin add https://github.com/proximiio/proximiio-cordova.git
```


### Usage ###


```
    onDeviceReady: function() {
        // execute on cordova/ionic device or platform ready

        proximiio.setDebugOutput(true, null, null);

        // set optional callbacks
        proximiio.setProximiioReadyCallback(function(visitorId) {});        
        proximiio.setInputTriggerCallback(function(enter, geofence) {});
        proximiio.setOutputTriggerCallback(function(output) {});
        proximiio.setPositionChangeCallback(function(position) {});
        proximiio.setBeaconFoundCallback(function(beacon) {});
        proximiio.setBeaconLostCallback(function(beacon) {});
        proximiio.setFloorChangedCallback(function(floor) {});

        // this method initializes Proximi.io
        proximiio.setToken(PROXIMIIO_TOKEN, function success() {
          console.log('proximiio setToken success');
        }, function failure(error) {
          console.log('proximiio setToken failure' + error);
        });
    },
```


### Android Gotchas ###

depending on your project configuration you may encounter a build error:

```
	uses-sdk:minSdkVersion 14 cannot be smaller than version 18 declared in library ....
```

in that case edit platforms/android/AndroidManifest.xml and replace

```
    <uses-sdk android:minSdkVersion="14" android:targetSdkVersion="22" />
with
    <uses-sdk android:minSdkVersion="18" android:targetSdkVersion="22" />
```
