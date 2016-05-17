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

import io.proximi.proximiiolibrary.Proximiio;
import io.proximi.proximiiolibrary.ProximiioFactory;
import io.proximi.proximiiolibrary.ProximiioGeofence;
import io.proximi.proximiiolibrary.ProximiioListener;
import io.proximi.proximiiolibrary.ProximiioFloor;

public class ProximiioCordova extends CordovaPlugin {
	private Proximiio proximiio;
	private String id;
	private String token;
	private boolean runOnBackground;
	private Activity activity;
	private static final String TAG = "ProximiioCordova";

    @Override
    public boolean execute(String action, CordovaArgs args, CallbackContext callbackContext) throws JSONException {
		activity = cordova.getActivity();
    	if (action.equals("setToken")) {
			if (proximiio == null) {
				token = args.getString(0);
				initProximiio();
			}
		} else if (action.equals("showPushMessage")) {

		} else if (action.equals("setRunOnBackground")) {
			runOnBackground = args.getBoolean(0);
		}
		return true;
    }

	private void initProximiio() {

		proximiio = ProximiioFactory.getProximiio(activity.getApplicationContext(), activity, new ProximiioListener() {
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

		});

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
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
	}
}
