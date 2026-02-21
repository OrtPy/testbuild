package com.sonymobile.experienceflow.wallpaper;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import com.sonymobile.experienceflow2.R;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ExperienceFlowPreferencesActivity extends PreferenceActivity {
    public static final String ENVENT_ACTION = "Select Color";
    public static final String ENVENT_CATEGORY = "Experience Flow Setting Color";
    public static final String ENVENT_VALUE = "1";
    private static final String LICENSE_FILE = "LICENSE.html";
    public static final String LOG_TAG = "ExperienceFlowPreferencesActivity";
    private static final int MENU_ID_LICENSE = 0;
    private static final String MIME_TYPE = "text/html";
    public static final String PREFS_KEY_COLOR = "preferences_color";
    public static final String SHARED_PREFS_NAME = "ExperienceFlowPrefs";
    private static final String UTF8_ENCODING = "utf-8";
    private static int sDirectionalityLeftToRightField;
    private static Method sSetDirectionalityMethod;
    /* access modifiers changed from: private */
    public AlertDialog mLicenseDialog;
    /* access modifiers changed from: private */
    public LoadLicenseTask mLoadLicenseTask;
    /* access modifiers changed from: private */
    public SharedPreferences mPreferences;
    /* access modifiers changed from: private */
    public ProgressDialog mProgressDialog;

    static {
        try {
            sDirectionalityLeftToRightField = ViewGroup.class.getDeclaredField("DIRECTIONALITY_LEFT_TO_RIGHT").getInt((Object) null);
            Class[] clsArr = new Class[1];
            clsArr[MENU_ID_LICENSE] = Integer.TYPE;
            sSetDirectionalityMethod = ViewGroup.class.getDeclaredMethod("setDirectionality", clsArr);
        } catch (SecurityException e) {
            Log.w(LOG_TAG, e.getMessage());
        } catch (NoSuchMethodException e2) {
            Log.w(LOG_TAG, e2.getMessage());
        } catch (NoSuchFieldException e3) {
            Log.w(LOG_TAG, e3.getMessage());
        } catch (IllegalAccessException e4) {
            Log.e(LOG_TAG, e4.getMessage());
        }
    }

    static final void setDirectionalityLeftToRight(ViewGroup vg) {
        if (sSetDirectionalityMethod != null) {
            try {
                Method method = sSetDirectionalityMethod;
                Object[] objArr = new Object[1];
                objArr[MENU_ID_LICENSE] = Integer.valueOf(sDirectionalityLeftToRightField);
                method.invoke(vg, objArr);
            } catch (IllegalAccessException e) {
                Log.e(LOG_TAG, "Failed to invoke setDirectionality: " + e.getMessage());
            } catch (InvocationTargetException e2) {
                Log.e(LOG_TAG, "Failed to invoke setDirectionality: " + e2.getMessage());
            }
        }
    }

    /* access modifiers changed from: protected */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActionBar().setDisplayHomeAsUpEnabled(true);
        this.mPreferences = getSharedPreferences(SHARED_PREFS_NAME, MENU_ID_LICENSE);
        setListAdapter(new ArrayAdapter<ColorInfo>(this, R.layout.settings_item, ColorPicker.getSemcColors(getApplicationContext())) {
            public View getView(int position, View convertView, ViewGroup parent) {
                View view = convertView;
                if (view == null) {
                    view = ((LayoutInflater) ExperienceFlowPreferencesActivity.this.getSystemService("layout_inflater")).inflate(R.layout.settings_item, (ViewGroup) null);
                    ExperienceFlowPreferencesActivity.setDirectionalityLeftToRight((ViewGroup) view);
                }
                ColorInfo color = (ColorInfo) getItem(position);
                ImageView imageView = (ImageView) view.findViewById(R.id.itemIcon);
                if (imageView != null) {
                    imageView.setImageDrawable(ExperienceFlowPreferencesActivity.this.getResources().getDrawable(color.thumbnailID));
                }
                TextView textView = (TextView) view.findViewById(R.id.itemText);
                if (textView != null) {
                    textView.setText(ExperienceFlowPreferencesActivity.this.getText(color.nameID));
                }
                return view;
            }
        });
        getListView().setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                ColorInfo color = (ColorInfo) parent.getItemAtPosition(position);
                if (color != null) {
                    ExperienceFlowPreferencesActivity.this.mPreferences.edit().putInt(ExperienceFlowPreferencesActivity.PREFS_KEY_COLOR, color.index).apply();
                }
                ExperienceFlowPreferencesActivity.this.finish();
            }
        });
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case MENU_ID_LICENSE /*0*/:
                if (this.mLoadLicenseTask == null) {
                    this.mLoadLicenseTask = new LoadLicenseTask();
                    this.mProgressDialog = ProgressDialog.show(this, getText(R.string.license_dialog_title), getText(R.string.license_loading), true, false);
                    this.mProgressDialog.setProgressStyle(MENU_ID_LICENSE);
                    LoadLicenseTask loadLicenseTask = this.mLoadLicenseTask;
                    Void[] voidArr = new Void[1];
                    voidArr[MENU_ID_LICENSE] = null;
                    loadLicenseTask.execute(voidArr);
                    break;
                }
                break;
            case 16908332:
                finish();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        menu.add(MENU_ID_LICENSE, MENU_ID_LICENSE, MENU_ID_LICENSE, R.string.license_dialog_title).setShowAsAction(4);
        return true;
    }

    /* access modifiers changed from: protected */
    public void onDestroy() {
        if (!(this.mLoadLicenseTask == null || this.mLoadLicenseTask.getStatus() == AsyncTask.Status.FINISHED)) {
            this.mLoadLicenseTask.cancel(true);
        }
        if (this.mProgressDialog != null) {
            if (this.mProgressDialog.isShowing()) {
                this.mProgressDialog.dismiss();
            }
            this.mProgressDialog = null;
        }
        if (this.mLicenseDialog != null) {
            if (this.mLicenseDialog.isShowing()) {
                this.mLicenseDialog.dismiss();
            }
            this.mLicenseDialog = null;
        }
        super.onDestroy();
    }

    /* access modifiers changed from: private */
    public void showLicenseDialog(String license) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(R.string.license_dialog_title);
        WebView webView = new WebView(this);
        builder.setView(webView);
        this.mLicenseDialog = builder.create();
        this.mLicenseDialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
            public void onDismiss(DialogInterface dialog) {
                LoadLicenseTask unused = ExperienceFlowPreferencesActivity.this.mLoadLicenseTask = null;
            }
        });
        webView.setWebViewClient(new WebViewClient() {
            public void onPageFinished(WebView view, String url) {
                if (ExperienceFlowPreferencesActivity.this.mProgressDialog != null) {
                    if (ExperienceFlowPreferencesActivity.this.mProgressDialog.isShowing()) {
                        ExperienceFlowPreferencesActivity.this.mProgressDialog.dismiss();
                    }
                    ProgressDialog unused = ExperienceFlowPreferencesActivity.this.mProgressDialog = null;
                    if (ExperienceFlowPreferencesActivity.this.mLicenseDialog != null) {
                        ExperienceFlowPreferencesActivity.this.mLicenseDialog.show();
                    }
                }
            }
        });
        webView.loadDataWithBaseURL((String) null, license, MIME_TYPE, UTF8_ENCODING, (String) null);
    }

    private class LoadLicenseTask extends AsyncTask<Void, Void, String> {
        private LoadLicenseTask() {
        }

        /* access modifiers changed from: protected */
        /* JADX WARNING: Removed duplicated region for block: B:15:0x0036 A[SYNTHETIC, Splitter:B:15:0x0036] */
        /* JADX WARNING: Removed duplicated region for block: B:29:0x0057 A[SYNTHETIC, Splitter:B:29:0x0057] */
        /* Code decompiled incorrectly, please refer to instructions dump. */
        public java.lang.String doInBackground(java.lang.Void... r10) {
            /*
                r9 = this;
                r4 = 0
                java.lang.StringBuilder r0 = new java.lang.StringBuilder
                r0.<init>()
                java.io.BufferedReader r5 = new java.io.BufferedReader     // Catch:{ IOException -> 0x0065 }
                java.io.InputStreamReader r6 = new java.io.InputStreamReader     // Catch:{ IOException -> 0x0065 }
                com.sonymobile.experienceflow.wallpaper.ExperienceFlowPreferencesActivity r7 = com.sonymobile.experienceflow.wallpaper.ExperienceFlowPreferencesActivity.this     // Catch:{ IOException -> 0x0065 }
                android.content.res.AssetManager r7 = r7.getAssets()     // Catch:{ IOException -> 0x0065 }
                java.lang.String r8 = "LICENSE.html"
                java.io.InputStream r7 = r7.open(r8)     // Catch:{ IOException -> 0x0065 }
                java.lang.String r8 = "utf-8"
                r6.<init>(r7, r8)     // Catch:{ IOException -> 0x0065 }
                r5.<init>(r6)     // Catch:{ IOException -> 0x0065 }
                r6 = 1024(0x400, float:1.435E-42)
                char[] r1 = new char[r6]     // Catch:{ IOException -> 0x002d, all -> 0x0062 }
            L_0x0022:
                int r3 = r5.read(r1)     // Catch:{ IOException -> 0x002d, all -> 0x0062 }
                if (r3 <= 0) goto L_0x003e
                r6 = 0
                r0.append(r1, r6, r3)     // Catch:{ IOException -> 0x002d, all -> 0x0062 }
                goto L_0x0022
            L_0x002d:
                r2 = move-exception
                r4 = r5
            L_0x002f:
                java.lang.String r6 = "ExperienceFlowPreferencesActivity"
                android.util.Log.w(r6, r2)     // Catch:{ all -> 0x0054 }
                if (r4 == 0) goto L_0x0039
                r4.close()     // Catch:{ IOException -> 0x004d }
            L_0x0039:
                java.lang.String r6 = r0.toString()
                return r6
            L_0x003e:
                if (r5 == 0) goto L_0x0067
                r5.close()     // Catch:{ IOException -> 0x0045 }
                r4 = r5
                goto L_0x0039
            L_0x0045:
                r2 = move-exception
                java.lang.String r6 = "ExperienceFlowPreferencesActivity"
                android.util.Log.w(r6, r2)
                r4 = r5
                goto L_0x0039
            L_0x004d:
                r2 = move-exception
                java.lang.String r6 = "ExperienceFlowPreferencesActivity"
                android.util.Log.w(r6, r2)
                goto L_0x0039
            L_0x0054:
                r6 = move-exception
            L_0x0055:
                if (r4 == 0) goto L_0x005a
                r4.close()     // Catch:{ IOException -> 0x005b }
            L_0x005a:
                throw r6
            L_0x005b:
                r2 = move-exception
                java.lang.String r7 = "ExperienceFlowPreferencesActivity"
                android.util.Log.w(r7, r2)
                goto L_0x005a
            L_0x0062:
                r6 = move-exception
                r4 = r5
                goto L_0x0055
            L_0x0065:
                r2 = move-exception
                goto L_0x002f
            L_0x0067:
                r4 = r5
                goto L_0x0039
            */
            throw new UnsupportedOperationException("Method not decompiled: com.sonymobile.experienceflow.wallpaper.ExperienceFlowPreferencesActivity.LoadLicenseTask.doInBackground(java.lang.Void[]):java.lang.String");
        }

        /* access modifiers changed from: protected */
        public void onPostExecute(String result) {
            ExperienceFlowPreferencesActivity.this.showLicenseDialog(result);
        }
    }
}
