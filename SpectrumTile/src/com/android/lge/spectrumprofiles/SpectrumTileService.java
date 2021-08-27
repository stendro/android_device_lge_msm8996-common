package com.android.lge.spectrumprofiles;

import android.service.quicksettings.Tile;
import android.service.quicksettings.TileService;
import android.graphics.drawable.Icon;
import android.os.SystemProperties;

public class SpectrumTileService extends TileService {
    
    static void setStringProp(String prop, String value) {
        SystemProperties.set(prop, value);
    }

    static String getStringProp(String prop) {
        return SystemProperties.get(prop);
    }
    static void setintProp(String prop, int value) {
        SystemProperties.set(prop, String.valueOf(value));
    }

    static int getintProp(String prop, int defaultValue) {
        return SystemProperties.getInt(prop, defaultValue);
    }

    public static final String SPECTRUM_PROP = "persist.spectrum.profile";
    private int mCurrentSetting;

    @Override
    public void onStartListening() {
        getQsTile().setState(Tile.STATE_ACTIVE);
        updateTile();
        super.onStartListening();
    }

    @Override
    public void onClick() {

	int currentState = SpectrumTileService.getintProp(SPECTRUM_PROP, 0);
        int nextState;
        if (currentState == 4) {
            nextState = 0;
        } else {
            nextState = currentState + 1;
        }

        Tile tile = getQsTile();
        SpectrumTileService.setintProp(SPECTRUM_PROP, nextState);
        updateTile();
        super.onClick();
    }
    private void updateTile() {
	int currentState = SpectrumTileService.getintProp(SPECTRUM_PROP, 0);
	if (currentState == 0){
		getQsTile().setIcon(Icon.createWithResource(this, R.drawable.ic_profile_balanced));
		getQsTile().setLabel(getString(R.string.balanced_profile_text));
	} else if (currentState == 1){
		getQsTile().setIcon(Icon.createWithResource(this, R.drawable.ic_notification_profile_high));
		getQsTile().setLabel(getString(R.string.high_performance_profile_text));
	} else if (currentState == 2){
		getQsTile().setIcon(Icon.createWithResource(this, R.drawable.ic_profile_power_save));
		getQsTile().setLabel(getString(R.string.power_save_profile_text));
	} else if (currentState == 3){
		getQsTile().setIcon(Icon.createWithResource(this, R.drawable.ic_gaming_notif));
		getQsTile().setLabel(getString(R.string.gaming_profile_text));
	} else {
		getQsTile().setIcon(Icon.createWithResource(this, R.drawable.ic_profile_bias_power_save));
		getQsTile().setLabel(getString(R.string.bias_power_save_profile_text));
	}
	getQsTile().updateTile();
  }
}
