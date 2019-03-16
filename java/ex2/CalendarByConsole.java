import java.util.Scanner;
import java.time.LocalDate;

public class CalendarByConsole{

	public static void main(String[] args) throws java.io.IOException{
		int year=666;
		Scanner scan = new Scanner(System.in);
		println("Please enter the year:");
		for (;;)
			if (scan.hasNextInt()) {
				year = scan.nextInt();
				if (year>0)
					break;
			}
			else
				scan.nextLine();
		printf(" %d年\n", year);
		calendarOfYear(year);
	}

	private static int days_of_month[]={31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public static void calendarOfYear(int year) { calendarOfYear(year, 3); }

	public static void calendarOfYear(int year, int col) {
		int i, j, row=12/col;
		String s[] = new String[col];

		for (i=0; i<row; ++i) {
			for (j=0; j<col; j++)
				s[j] = "".format(" %2d月%20c\n", i*col+j+1, ' ') + getCalendarString(year, i*col+j+1);
			merge_print(col, s);
			System.out.write('\n');
		}
	}

	public static String getCalendarString(int year, int month) {
		int i, line=0;
		int weekfix = LocalDate.of(year, month, 1).getDayOfWeek().getValue()%7;
		String linefix = "".format("%4c\n", ' ');
		StringBuilder str = new StringBuilder(" 日 一 二 三 四 五 六" + linefix);

		if (month == 2)
			days_of_month[1] = 28 + leap(year);
		--month;
		for (i=0; i<weekfix; ++i)
			str.append("   ");
		for (i=1; i<=days_of_month[month]; ++i) {
			str.append("".format("%3d", i));
			if ((i+weekfix)%7 == 0) {
				str.append(linefix);
				++line;
			}
		}
		if ((--i+weekfix)%7 != 0) {
			while ((++i+weekfix)%7 != 0 )
				str.append("   ");
			str.append("   " + linefix);
			++line;
		}
		while (++line<=6)
			str.append("".format("%21c", ' ') + linefix);
		return str.toString();
	}

	public static void merge_print(int n, String... str) {
		int i;
		int lf[] = new int[n];
		int rlf[] = new int[n];

		for (;;) {
			for (i=0; i<n; ++i) {
				lf[i] = str[i].indexOf('\n', lf[i]);
				if (lf[i]<0)
					return;
				print(str[i].substring(rlf[i], lf[i]));
				rlf[i] = ++lf[i];
			}
			System.out.write('\n');
		}
	}

	private static int leap(int year) {
		return year%4==0 && year%100!=0 ? 1 : (year%400==0 ? 1 : 0);
	}
	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
