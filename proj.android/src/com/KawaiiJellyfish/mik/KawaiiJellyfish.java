/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.KawaiiJellyfish.mik;

import gameutil.JNIProxy;

import org.cocos2dx.lib.Cocos2dxActivity;


import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

public class KawaiiJellyfish extends Cocos2dxActivity{
	
	public static Handler m_handler = null;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		JNIProxy.init(this);
		
		m_handler = new  Handler(){

			@Override
			public void handleMessage(Message msg) {
				// TODO Auto-generated method stub
				switch(msg.what){
				case 0:
					Toast.makeText(KawaiiJellyfish.this, (msg.obj == null) ? getResources().getString(R.string.IllegalArgumentException_msg) : (getResources().getString(R.string.IllegalArgumentException_msg) + String.valueOf(msg.obj)), Toast.LENGTH_SHORT).show();
					break;
				case 1:
					Toast.makeText(KawaiiJellyfish.this, (msg.obj == null) ? getResources().getString(R.string.IllegalArgumentException_msg) : (getResources().getString(R.string.IllegalArgumentException_msg) + String.valueOf(msg.obj)), Toast.LENGTH_SHORT).show();
					break;
				case 2:
					Toast.makeText(KawaiiJellyfish.this, (msg.obj == null) ? getResources().getString(R.string.IllegalArgumentException_msg) : (getResources().getString(R.string.IllegalArgumentException_msg) + String.valueOf(msg.obj)), Toast.LENGTH_SHORT).show();
					break;
//				case 9:
//					WeiboUitls.getInstance().getWeiboAuth().authorize((WeiboAuthListener) msg.obj, msg.arg1);
//					break;
				default:
					break;
				}
			}
			
		};
	}
	
    static {
         System.loadLibrary("kawaiijellyfish");
    }

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		JNIProxy.destory();
	}
    
    
}
