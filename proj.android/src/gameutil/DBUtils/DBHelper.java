package gameutil.DBUtils;

import com.KawaiiJellyfish.mik.*;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DBHelper extends SQLiteOpenHelper {

	public DBHelper(Context context) {
		super(context, context.getString(R.string.sqliteDB_Name),null, 1);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		// TODO Auto-generated method stub
		String sql = "CREATE TABLE IF NOT EXISTS UserDefault(_id INTEGER PRIMARY KEY AUTOINCREMENT, dataKey TEXT unique, dataValue TEXT)";
		db.execSQL(sql);
		Log.d("sql create table", sql.toString());
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		// TODO Auto-generated method stub
	}
	
	
}
