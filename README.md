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
        proximiio.setIDandAuthToken("YOUR_APP_ID", "YOUR_TOKEN", null, null);
        proximiio.setDebugOutput(true, null, null);
        proximiio.setOutputTriggerCallback(function (output, input) {
            if(output.type != "XHTML")
                return;
            // your code here
        });
        proximiio.setInputTriggerCallback(function(input, entered) {
            if(entered == false)
                return;
            // your code here
        });
        proximiio.setPositionChangeCallback(function(coords) {
            // your code here
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

Also make sure the app has multidex enabled, 

```
    <application android:name="android.support.multidex.MultiDexApplication" ... >...</application>
```