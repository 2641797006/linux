import java.time.LocalDate;
import javafx.scene.paint.Color;

public final class __{
	public static String merge_to_print(int n, String ins, String... str) {
		return merge_to_print(n, '\n', "", ins, "", str);
	}

	public static String merge_to_print(int n, char delim, String left, String ins, String right, String... str) {
		int i;
		int lf[] = new int[n];
		int rlf[] = new int[n];
		StringBuilder mstr = new StringBuilder();

		for (;;) {
			mstr.append(left);
			for (i=0; ; ) {
				lf[i] = str[i].indexOf(delim, lf[i]);
				if (lf[i]<0)
					return mstr.toString();
				mstr.append(str[i].substring(rlf[i], lf[i]));
				rlf[i] = ++lf[i];
				if (++i<n)
					mstr.append(ins);
				else
					break;
			}
			mstr.append(right);
			mstr.append('\n');
		}
	}

	public static Color RGB(int rgb) {
		return RGB(rgb, 1);
	}

	public static Color RGB(int rgb, double opacity) {
		final double q = 0xff;
		return new Color((rgb>>16)/q, (rgb>>8 & 0xff)/q, (rgb & 0xff)/q, opacity);
	}

	public static String calendarOfYear(int year) {
		return calendarOfYear(year, 4);
	}

	public static String calendarOfYear(int year, int col) {
		int i, j, row=12/col;
		String s[] = new String[col];
		StringBuilder str = new StringBuilder();
		str.append('\n');

		for (i=0; i<row; ++i) {
			for (j=0; j<col; j++)
				s[j] = "".format("%6c%2d月%10c\n", ' ', i*col+j+1, ' ') + getCalendarString(year, i*col+j+1);
			str.append(merge_to_print(col, '\n', " ", "    ", " ", s));
			str.append('\n');
		}
		str.deleteCharAt(str.length()-1);
		return str.toString();
	}

	public static String getCalendarString(int year, int month) {
		int i, line=0;
		int weekfix = LocalDate.of(year, month, 1).getDayOfWeek().getValue()%7;
		StringBuilder str = new StringBuilder("日 一 二 三 四 五 六\n");

		if (month == 2)
			days_of_month[1] = 28 + leap(year);
		--month;
		for (i=0; i<weekfix; ++i)
			str.append("   ");
		for (i=1; i<=days_of_month[month]; ++i) {
			str.append("".format("%2d ", i));
			if ((i+weekfix)%7 == 0) {
				str.setCharAt(str.length()-1, '\n');
				++line;
			}
		}
		if ((--i+weekfix)%7 != 0) {
			while ((++i+weekfix)%7 != 0 )
				str.append("   ");
			str.append("  \n");
			++line;
		}
		while (++line<=6)
			str.append("".format("%20c\n", ' '));
		return str.toString();
	}

	public static int leap(int year) {
		return year%4==0 && year%100!=0 ? 1 : (year%400==0 ? 1 : 0);
	}

	private static int days_of_month[]={31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public static void print(String s) {System.out.print(s);}
	public static void println(String s) {System.out.println(s);}
	public static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
