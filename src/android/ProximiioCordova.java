package com.navtureapps.cordovaplugin;

import org.apache.cordova.*;
import org.json.JSONException;
import android.widget.Toast;
import android.app.Activity;
import android.util.Log;
import android.content.Intent;
import java.lang.Runnable;
import java.util.ArrayList;
import org.json.JSONObject;
import android.support.annotation.Nullable;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat.OnRequestPermissionsResultCallback;
import javax.security.auth.callback.Callback;
import com.navtureapps.cordovaplugin.PermissionHelper;
import io.proximi.proximiiolibrary.Proximiio;
import io.proximi.proximiiolibrary.ProximiioFactory;
import io.proximi.proximiiolibrary.ProximiioGeofence;
import io.proximi.proximiiolibrary.ProximiioListener;
import io.proximi.proximiiolibrary.ProximiioFloor;
import android.Manifest;
import android.os.Build;

public class ProximiioCordova extends CordovaPlugin implements OnRequestPermissionsResultCallback {
  private Proximiio proximiio;
  private ProximiioListener listener;
  private String id;
  private String token;
  private boolean runOnBackground;
  private Activity activity;
  private static final String TAG = "ProximiioCordova";
  CallbackContext context;

  private static final String ACTION_SET_TOKEN = "setToken";
  private static final String ACTION_SHOW_PUSH_MESSAGE = "showPushMessage";
  private static final String ACTION_SET_RUN_ON_BACKGROUND = "setRunOnBackground";

  String [] permissions = { Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_FINE_LOCATION };

  @Override
  public boolean execute(String action, CordovaArgs args, CallbackContext callbackContext) throws JSONException {
    activity = cordova.getActivity();
    context = callbackContext;
    cordova.setActivityResultCallback(this);
    if (action.equals(ACTION_SET_TOKEN)) {
        if (proximiio == null) {
          token = args.getString(0);
          if(hasPermisssion()) {
              PluginResult r = new PluginResult(PluginResult.Status.OK);
              context.sendPluginResult(r);
              return true;
          }
          else {
              PermissionHelper.requestPermissions(this, 0, permissions);
          }
          return true;
        }
    } else if (action.equals(ACTION_SHOW_PUSH_MESSAGE)) {

    } else if (action.equals(ACTION_SET_RUN_ON_BACKGROUND)) {
      runOnBackground = args.getBoolean(0);
    }
    return true;
  }

  private void initProximiio() {
    proximiio = ProximiioFactory.getProximiio(activity, activity);
    listener = new ProximiioListener() {
      @Override
      public void geofenceEnter(final ProximiioGeofence geofence) {
        Log.d(TAG, "Geofence enter: " + geofence.getName());
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
          String geofenceJson = geofence.getJSON().toString();
          webView.loadUrl("javascript:proximiio.triggeredInput(1, " + geofenceJson + ")");
            }
        });
      }

      @Override
      public void geofenceExit(final ProximiioGeofence geofence) {
        Log.d(TAG, "Geofence exit: " + geofence.getName());
        activity.runOnUiThread(new Runnable() {
          @Override
          public void run() {
          String geofenceJson = geofence.getJSON().toString();
          webView.loadUrl("javascript:proximiio.triggeredInput(0, " + geofenceJson + ")");
          }
        });
      }

      @Override
      public void changedFloor(@Nullable ProximiioFloor floor) {
        if (floor != null) {
          Log.d(TAG, "changedFloor: " + floor.getName());
          final String floorJson = floor.getJSON().toString();
          activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                        webView.loadUrl("javascript:proximiio.changedFloor(0, " + floorJson + ")");
                }
          });
        }
      }

      @Override
      public void position(final double lat, final double lon, final double accuracy) {
        activity.runOnUiThread(new Runnable() {
          @Override
          public void run() {
          String action = "javascript:proximiio.updatedPosition({coordinates:{lat:" + lat + ", lon:" + lon + "}, accuracy:" + accuracy + "})";
          Log.d(TAG, "position update action: " + action);
          webView.loadUrl(action);
          }
        });
      }

      @Override
      public void loginFailed(LoginError loginError) {
        Log.e(TAG, "LoginError! (" + loginError.toString() + ")");
      }


      /**
       * Push output from Proximiio
       * @param title Text received
       * @return Is this push handled? (If not, Proximiio generates a snackbar)
       */
      @Override
      public boolean push(String title) {
        return true;
      }

      /**
      * Receives JSON payloads from Proximiio events' outputs.
      * @param json JSON received as specified in payload.
      */
      @Override
      public void output(final JSONObject json) {
        Log.d(TAG, "output received!");
        Log.d(TAG, "output received:" + json.toString());
        activity.runOnUiThread(new Runnable() {
          @Override
          public void run() {
            Log.d(TAG, "output received:" + json.toString());
            webView.loadUrl("javascript:proximiio.triggeredOutput(" + json.toString() + ")");
          }
        });
      }

    };

    proximiio.addListener(listener);

    // Login to Proximi.io
    proximiio.setAuth(token);

    activity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
      Toast.makeText(activity, "Init success!", Toast.LENGTH_SHORT).show();
      }
    });
  }

  @Override
  public void onStart() {
    activity = cordova.getActivity();
    if (id != null && token != null) {
      initProximiio();
    }
  }

  @Override
  public void onStop() {
      super.onStop();
      proximiio.removeListener(listener);
  }

  @Override
  public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
      activity.onRequestPermissionsResult(requestCode, permissions, grantResults);
      proximiio.onRequestPermissionsResult(requestCode, permissions, grantResults);
  }

  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent data) {
      super.onActivityResult(requestCode, resultCode, data);
      proximiio.onActivityResult(requestCode, resultCode, data);
  }

  public void onRequestPermissionResult(int requestCode, String[] permissions,
                                        int[] grantResults) throws JSONException {
      PluginResult result;
      for(int r:grantResults)
      {
          if(r == PackageManager.PERMISSION_DENIED)
          {
              LOG.d(TAG, "Permission Denied!");
              result = new PluginResult(PluginResult.Status.ILLEGAL_ACCESS_EXCEPTION);
              context.sendPluginResult(result);
              return;
          }
      }
      result = new PluginResult(PluginResult.Status.OK);
      initProximiio();
      context.sendPluginResult(result);
  }

  public boolean hasPermisssion() {
      for(String p : permissions)
      {
          if(!PermissionHelper.hasPermission(this, p))
          {
              return false;
          }
      }
      return true;
  }

  /*
   * We override this so that we can access the permissions variable, which no longer exists in
   * the parent class, since we can't initialize it reliably in the constructor!
   */

  public void requestPermissions(int requestCode) {
      PermissionHelper.requestPermissions(this, requestCode, permissions);
  }
}
