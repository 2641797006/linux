import java.util.Scanner;
import java.time.LocalDate;
import javax.swing.JOptionPane;

public class
xx1{
//CalendarByConsole{

	public static void main(String[] args) throws java.io.IOException{
		int year=0;
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
		print(calendarOfYear(year, 3));
		JOptionPane.showMessageDialog(null, calendarOfYear(year, 4), "".format(" %d年", year), JOptionPane.PLAIN_MESSAGE);
	}

	private static int days_of_month[]={31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public static String calendarOfYear(int year, int col) {
		int i, j, row=12/col;
		String s[] = new String[col];
		StringBuilder str = new StringBuilder();

		for (i=0; i<row; ++i) {
			for (j=0; j<col; j++)
				s[j] = "".format("%13c%2d月%15c\n", ' ', i*col+j+1, ' ') + getCalendarString(year, i*col+j+1);
			str.append(merge_print_string(col, s));
			str.append('\n');
		}
		return str.toString();
	}

	public static String getCalendarString(int year, int month) {
		int i, line=0;
		int weekfix = LocalDate.of(year, month, 1).getDayOfWeek().getValue()%7;
		String linefix = "".format("%4c\n", ' ');
		StringBuilder str = new StringBuilder(" SUN MON TUE WED THU FRI SAT" + linefix);

		if (month == 2)
			days_of_month[1] = 28 + leap(year);
		--month;
		for (i=0; i<weekfix; ++i)
			str.append("    ");
		for (i=1; i<=days_of_month[month]; ++i) {
			str.append("".format("%4d", i));
			if ((i+weekfix)%7 == 0) {
				str.append(linefix);
				++line;
			}
		}
		if ((--i+weekfix)%7 != 0) {
			while ((++i+weekfix)%7 != 0 )
				str.append("    ");
			str.append("    " + linefix);
			++line;
		}
		while (++line<=6)
			str.append("".format("%28c", ' ') + linefix);
		return str.toString();
	}

	public static String merge_print_string(int n, String... str) {
		int i;
		int lf[] = new int[n];
		int rlf[] = new int[n];
		StringBuilder mstr = new StringBuilder();

		for (;;) {
			for (i=0; i<n; ++i) {
				lf[i] = str[i].indexOf('\n', lf[i]);
				if (lf[i]<0)
					return mstr.toString();
				mstr.append(str[i].substring(rlf[i], lf[i]));
				rlf[i] = ++lf[i];
			}
			mstr.append('\n');
		}
	}

	private static int leap(int year) {
		return year%4==0 && year%100!=0 ? 1 : (year%400==0 ? 1 : 0);
	}
	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
