package com.example.weldissonaraujo.webviewapp;
import android.content.Intent;
import android.net.Uri;
import android.webkit.WebView;
import android.webkit.WebViewClient;
/**
 * Created by weldisson.araujo on 09/11/2017.
 */

public class MyAppWebViewClient  extends WebViewClient {
    @Override
    public boolean shouldOverrideUrlLoading(WebView view, String url) {
		// inserir a url desejada
        if (Uri.parse(url).getHost().endsWith("https://thingspeak.com/channels/359681/charts/1?bgcolor=%23ffffff&color=%23d12020&dynamic=true&results=30&type=line&update=15")) {
            return false;
        }

        Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        view.getContext().startActivity(intent);
        return true;
    }
}
