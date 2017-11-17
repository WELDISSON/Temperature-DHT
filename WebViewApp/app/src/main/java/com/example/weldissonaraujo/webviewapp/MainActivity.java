package com.example.weldissonaraujo.webviewapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;


public class MainActivity extends AppCompatActivity {
    private WebView mWebView;

    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mWebView = (WebView) findViewById(R.id.activity_main_webview);

        // Força links e redireciona para abrir no WebView em vez de em um navegador
        mWebView.setWebViewClient(new WebViewClient());

        // Enable Javascript
        WebSettings webSettings = mWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);

        // colar a url
        mWebView.loadUrl("https://thingspeak.com/channels/359681/charts/1?bgcolor=%23ffffff&color=%23d12020&dynamic=true&results=30&type=line&update=15");

        // Pare links e redirecionamentos locais de abertura no navegador em vez de WebView
        mWebView.setWebViewClient(new MyAppWebViewClient());

        
    }

    // Impedir que o back-button feche o aplicativo
    @Override
    public void onBackPressed() {
        if(mWebView.canGoBack()) {
            mWebView.goBack();
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflar o menu; Isso adiciona itens à barra de ação se estiver presente.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        
		// Acionar o item da barra de ação, clique aqui. A barra de ação
        // lida automaticamente com cliques no botão Home / Up, por tanto tempo
        // como você especifica uma atividade pai no AndroidManifest.xml.
        int id = item.getItemId();

        //sem inspeção SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
