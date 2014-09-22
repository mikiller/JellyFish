package gameutil.DBUtils;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

public class DBManager {
	private DBHelper dbHelper = null;
	private SQLiteDatabase db = null;

	public DBManager(Context context) {
		dbHelper = new DBHelper(context);
		// db = dbHelper.getWritableDatabase();
	}

	public boolean insertData(String dataKeys[], String dataValues[]) {
		boolean rst = false;

		if (db == null)
			db = dbHelper.getWritableDatabase();
		db.beginTransaction();
		try {
			if (dataKeys == null || dataKeys.length == 0 || dataValues == null
					|| dataValues.length == 0)
				return rst;
			String sql = "replace into UserDefault(dataKey,dataValue) values(?,?)";
			for (int i = 0; i < dataKeys.length; i++) {
				db.execSQL(sql, new Object[]{dataKeys[i],dataValues[i]});
				rst = true;
				
			}
			db.setTransactionSuccessful();
		} finally {
			
			db.endTransaction();
			//closeDB();
		}
		return rst;
	}

	public boolean insertData(String dataKey, String dataValue) {
		boolean rst = false;

		if (db == null)
			db = dbHelper.getWritableDatabase();
		if (dataKey == null || dataKey == "" || dataValue == null
				|| dataValue == "")
			return rst;

		String sql = "replace into UserDefault(dataKey,dataValue) values(?,?)";
		db.execSQL(sql, new Object[] { dataKey, dataValue });
		rst = true;

		return rst;
	}

	public void updateData(String dataKeys[], String dataValues[]) {
		if (db == null)
			db = dbHelper.getWritableDatabase();
		ContentValues cv = new ContentValues();
		for (int i = 0; i < dataKeys.length; i++) {
			cv.put("dataValue", dataValues[i]);
			db.update("UserDefault", cv, "dataKey = ?",
					new String[] { dataKeys[i] });
		}
	}

	public String readData(String dataKey) {
		if (db == null)
			db = dbHelper.getWritableDatabase();
		Cursor c = db.query("UserDefault", new String[] { "dataValue" },
				"dataKey = ?", new String[] { dataKey }, null, null, null);
		if (!c.moveToFirst())
			return "";
		return c.getString(c.getColumnIndex("dataValue"));
	}

	public void closeDB() {
		if (db.isOpen())
			db.close();
		db = null;
	}

	private boolean isDataKeyExist(String dataKey) {
		Cursor c = db.query("UserDefault", null, null, null, null, null, null);
		if (!c.moveToFirst())
			return false;
		while (c.moveToNext()) {
			if (dataKey.equals(c.getString(c.getColumnIndex("dataKey")))) {
				return true;
			}
		}
		c.close();
		return false;
	}

}
