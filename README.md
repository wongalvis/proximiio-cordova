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
        console.log('onDeviceReady');
        proximiio.setToken(PROXIMIIO_TOKEN);
        //proximiio.setDebugOutput(true, null, null);

        proximiio.setOutputTriggerCallback(function (output) {
          // Your code here
        });

        proximiio.setInputTriggerCallback(function(enter, geofence) {
          // Your code here
        });

        proximiio.setPositionChangeCallback(function(coords) {
          // Your code here, for example:
          //document.getElementById("position-latitude").innerHTML = coords.coordinates.lat;
          //document.getElementById("position-longitude").innerHTML = coords.coordinates.lon;
          //document.getElementById("position-accuracy").innerHTML = coords.accuracy;
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
