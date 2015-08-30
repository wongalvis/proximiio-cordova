package com.navtureapps.cordovaplugin;

import org.apache.cordova.*;
import org.json.JSONException;
import com.navtureapps.proximiioandroid.Proximiio;
import com.navtureapps.proximiioandroid.ProximiioInput;
import com.navtureapps.proximiioandroid.ProximiioActionFlow;
import com.navtureapps.proximiioandroid.ProximiioOutput;
import com.navtureapps.proximiioandroid.ProximiioListener;
import android.widget.Toast;
import android.app.Activity;
import android.util.Log;
import android.content.Intent;
import java.lang.Runnable;
import java.util.ArrayList;

public class ProximiioCordova extends CordovaPlugin {
	private Proximiio proximiio;
	private String id;
	private String token;
	private boolean runOnBackground;
	private Activity activity;

    @Override
    public boolean execute(String action, CordovaArgs args, CallbackContext callbackContext) throws JSONException {
		Log.d("ProximiioCordova execute:", args.getString(0) + ", " + args.getString(1));
		activity = cordova.getActivity();
        if (action.equals("setIDandAuthToken")) {
			if (proximiio == null) {
				id = args.getString(0);
				token = args.getString(1);
				initProximiio();
			}
			else {
				id = args.getString(0);
				proximiio.setAppID(id);
			}
		}
		else if (action.equals("showPushMessage")) {

		}
		else if (action.equals("setRunOnBackground")) {
			runOnBackground = args.getBoolean(0);
		}
		return true;
    }

	private void initProximiio() {
		ProximiioListener listener = new ProximiioListener() {
			@Override
			public void eventEnter(final ProximiioInput input) {
				activity.runOnUiThread(new Runnable() {
					@Override
					public void run() {
            input.handleOutput(activity, null, true, false);
						ProximiioActionFlow actionFlow = input.getActionFlow();
						ArrayList<ProximiioOutput> outputs;
						if (actionFlow != null) {
						  outputs = actionFlow.getOutputs();
						} else {
							outputs = new ArrayList<ProximiioOutput>();
						}

						String inputJson = getInputJSON(input.getType() == ProximiioInput.InputType.iBeacon, input);
						webView.loadUrl("javascript:proximiio.triggeredInput(" + (input.getEntered() ? 1 : 0) + ", " + inputJson + ")");
						String outputJson = getOutputJSON(outputs);
						Log.d("ProximiioCordova", "outputJSON:" + outputJson);
						webView.loadUrl("javascript:proximiio.triggeredOutput(" + outputJson + ", " + inputJson + ")");
					}
				});
				Log.d("ProximiioCordova", "eventEnter");
			}

			@Override
			public void eventLeave(final ProximiioInput input) {
				activity.runOnUiThread(new Runnable() {
					@Override
					public void run() {
            input.handleOutput(activity, null, true, false);
						ProximiioActionFlow actionFlow = input.getActionFlow();
						ArrayList<ProximiioOutput> outputs;
						if (actionFlow != null) {
						  outputs = actionFlow.getOutputs();
						} else {
							outputs = new ArrayList<ProximiioOutput>();
						}
						String inputJson = getInputJSON(input.getType() == ProximiioInput.InputType.iBeacon, input);
						webView.loadUrl("javascript:proximiio.triggeredInput(" + (input.getEntered() ? 1 : 0) + ", " + inputJson + ")");
						String outputJson = getOutputJSON(outputs);
						Log.d("ProximiioCordova", "outputJSON:" + outputJson);
						webView.loadUrl("javascript:proximiio.triggeredOutput(" + outputJson + ", " + inputJson + ")");
					}
				});
				Log.d("ProximiioCordova", "eventLeave");
			}

			@Override
			public void positionChange(final double lat, final double lon, final double accuracy, final ProximiioInput.InputType inputType) {
				activity.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						webView.loadUrl("javascript:proximiio.updatedPosition(({coordinates:{lat:" + lat + ", lon:" + lon + "}, accuracy:" + accuracy + ", type:'" + inputType.toString() + "'}))");
					}
				});
				Log.d("ProximiioCordova", "positionChange");
			}

			@Override
			public void error(final Error error) {
				activity.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						Toast.makeText(activity, error.toString(), Toast.LENGTH_SHORT).show();
					}
				});
			}
		};

		proximiio = new Proximiio(activity, id, token, listener);

		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(activity, "Init success!", Toast.LENGTH_SHORT).show();
			}
		});
	}

	private String getInputJSON(boolean iBeacon, ProximiioInput input) {
		if (iBeacon) {
			return "({type:'iBeacon', id:'" + input.getId() + "', name:'" + input.getName() +
				   "', accuracy:" + input.getAccuracy() + ", coordinates:{lat:" + input.getLat() +
				   ", lon:" + input.getLon() + "}, departmentid:'" + input.getDepartmentID() +
				   "', entered:" + (input.getEntered() ? 1 : 0) + ", beacon:{uuid:'" +
				   input.getIBeacon().getUUID() + "', major:" + input.getIBeacon().getMajor() +
				   ", minor:" + input.getIBeacon().getMinor() + ", accuracy:" + input.getIBeacon().getAccuracy() + "}})";
		}
		else {
			return "({type:'" + input.getType().toString() + "', id:'" + input.getId() + "', name:'" +
				   input.getName() + "', accuracy:" + input.getAccuracy() + ", coordinates:{lat:" +
				   input.getLat() + ", lon:" + input.getLon() + "}, departmentid:'" +
				   input.getDepartmentID() + "', entered:" + (input.getEntered() ? 1 : 0) + "}})";
		}
	}

	private String getOutputJSON(ArrayList<ProximiioOutput> outputs) {
		String json = "([";
		for (ProximiioOutput output : outputs) {
			json = json + "{id:'"+output.getID()+"', type:'"+output.getType()+"', title:'"+output.getTitle() +
						 "', content:'" + output.getContent() + "'}";
		}
		json.replaceAll("\\}\\{", "\\}, \\{");
		return json + "])";
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
		if (runOnBackground) {
            proximiio.stopActivity();
        }
        else {
            proximiio.onDestroy();
        }
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(activity, "Stopping, left on background: " + String.valueOf(runOnBackground), Toast.LENGTH_SHORT).show();
			}
		});
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (proximiio != null) {
			proximiio.onActivityResult(requestCode, resultCode);
		}
	}
}
