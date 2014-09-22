package gameutil;

import gameutil.DBUtils.DBManager;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

import javax.crypto.EncryptedPrivateKeyInfo;

import org.xmlpull.v1.XmlSerializer;

import com.KawaiiJellyfish.mik.*;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Message;
import android.util.Log;
import android.view.Display;

public class JNIProxy {
	private static Context context = null;
	private static KawaiiJellyfish s_activity = null;
	private static Display display = null;

	private static DBManager dbm = null;

	private static Field[] fields = null;
	
	private static ArrayList<String> dirPath = null;

	public static Context getContext() {
		return context;
	}

	public static Activity getS_activity() {
		return s_activity;
	}

	public static void init(Activity activity) {
		s_activity = (KawaiiJellyfish) activity;
		display = activity.getWindowManager().getDefaultDisplay();

		dbm = new DBManager(s_activity);
	}

	public static String getStrFromXml(String key) {
		String str = "no value";
		
		try {
			str = XMLUtils.getStrFromXml(s_activity, key);
		} catch (IllegalArgumentException e) {
			s_activity.m_handler.sendEmptyMessage(0);
		} catch (IllegalAccessException e) {
			s_activity.m_handler.sendEmptyMessage(1);
		} catch (NoSuchFieldException e) {
			s_activity.m_handler.sendEmptyMessage(2);
		}
		
		return str;
	}

	public static String[] getStringsFromXml(String[] keys) {
		String[] strs = XMLUtils.getStringsFromXml(s_activity, keys);
		
		return strs;
	}

	public static boolean saveDataToSqlite(final String dataKeys[],
			final String dataValues[]) {
		new Thread(new Runnable() {

			@Override
			public void run() {
				dbm.insertData(dataKeys, dataValues);
			}
		}).start();
		return true;
	}
	
	public static boolean saveDataToSqlite(final String dataKey, final String dataValue){
		dbm.insertData(dataKey, dataValue);			
			
		return true;
	}

	public static String readDataFromSqlite(String dataKey) {
		return dbm.readData(dataKey);
	}

	public static void destory() {
		dbm.closeDB();
	}
	
//	public static void upload(String content, String file){
//		WeiboUitls.getInstance().initWeiboAuth(s_activity);
//		WeiboUitls.getInstance().upload(content, file);
//	}

	public static String[] traverseAssets(String rootPath){
			dirPath = new ArrayList<String>();
			getAllDirName("");
			//refreshFileList(rootPath);
			//getFiles("file:///android_asset/");
			String[] rst = dirPath.toArray(new String[0]);
			return rst;
	}
	
//	public static void refreshFileList(String strPath) {
//        File dir = new File(strPath);
//        File[] files = dir.listFiles();
//       
//        if (files == null)
//            return;
//        for (int i = 0; i < files.length; i++) {
//            if (files[i].isDirectory()) {
//            	Log.d("dir name", files[i].getName());
//                refreshFileList(files[i].getAbsolutePath());
//            } else {
//                String strFileName = files[i].getAbsolutePath().toLowerCase();
//                Log.d("file name:",strFileName);                   
//            }
//        }
//    }
	
	public static void getAllDirName(String path){
		boolean haslogged = false;
		try {
			String[] paths = s_activity.getAssets().list(path);

			for(int i = 0; i < paths.length; i++){
				if(paths[i].equals("images") || paths[i].equals("sounds") || paths[i].equals("webkit"))
					continue;
				if(!haslogged){
					Log.d("dir name",path);
					if(!path.equals(""))
						dirPath.add(path);
					haslogged = true;
				}
				if(!path.equals("")){
					File file = new File(path + "/" + paths[i]);
					if(!file.isDirectory())
						continue;
					getAllDirName(path + "/" + paths[i]);
					
				}
				else{
					File file = new File(paths[i]);
					if(!file.isDirectory())
						continue;
					getAllDirName(paths[i]);
				}
//				String[] subp = s_activity.getAssets().list(paths[i]);
//				for(int j = 0; j < subp.length; j++){
//					Log.d("subp",subp[j]);
//				}
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
//	public static void getFiles(String filePath) {
//		File root = new File(filePath);
//		File[] files = root.listFiles();
//		for (File file : files) {
//			if (file.isDirectory()) {
//				/*
//				 * 递归调用
//				 */
//				dirPath.add(file.getAbsolutePath());
//				getFiles(file.getAbsolutePath());
//				// filelist.add(file.getAbsolutePath());
//				System.out.println("显示" + filePath + "下所有子目录及其文件"
//						+ file.getAbsolutePath());
//			} else {
//				System.out.println("显示" + filePath + "下所有子目录"
//						+ file.getAbsolutePath());
//			}
//		}
//	}
	
	
}
