package gameutil;

import java.util.ArrayList;

import com.KawaiiJellyfish.mik.*;

import android.content.Context;
import android.os.Message;
import android.util.Log;

public class XMLUtils {
	
	public static String getStrFromXml(Context context, String key) throws IllegalArgumentException, IllegalAccessException, NoSuchFieldException{
		String str = "no value";
			str = context.getResources().getString(
					(Integer) R.string.class.getField(key).get(R.string.class));

			Log.d("str", str);
		
		return str;
	}

	public static String[] getStringsFromXml(Context context, String[] keys){
		String[] strs = new String[] {};
		ArrayList<String> temp = new ArrayList<String>();
		for (int i = 0; i < keys.length; i++) {
			try {
				temp.add(getStrFromXml(context, keys[i]));
			} catch (IllegalArgumentException e) {
				sendMsgToHandler(context, 0, keys[i]);
			} catch (IllegalAccessException e) {
				sendMsgToHandler(context, 1, keys[i]);
			} catch (NoSuchFieldException e) {
				sendMsgToHandler(context, 2, keys[i]);
			}
		}
		strs = (String[]) temp.toArray();
		return strs;
	}
	
	
	private static void sendMsgToHandler(Context context, int what, Object obj){
		Message msg = new Message();
		msg.what = 0;
		msg.obj = obj;
		if(context instanceof KawaiiJellyfish){
			((KawaiiJellyfish) context).m_handler.sendMessage(msg);
		}
	}
}
