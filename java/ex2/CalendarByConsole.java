import java.util.Scanner;
import java.time.LocalDate;

public class CalendarByConsole{

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
		calendarOfYear(year);
	}

	private static int days_of_month[]={31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public static void calendarOfYear(int year) {__calendarOfYear(year, 3);}

	public static void __calendarOfYear(int year, int col) {
		int i, j, row=12/col;
		int lf[] = new int[col];
		int rlf[] = new int[col];
		String s[] = new String[col];
		String linefix = "".format("%4c", ' ');
		String blankline = "".format("%21c", ' ') + linefix;

		for (i=0; i<row; i++) {
			for (j=0; j<col; j++) {
				rlf[j] = 0;
				lf[j] = -1;
				s[j] = "".format(" %2d月%16c\n", i*col+j+1, ' ') + getCalendarString(year, i*col+j+1);
			}
			do {
				for (j=0; j<col; j++) {
					lf[j] = s[j].indexOf('\n', lf[j]+1);
					if (lf[j]<0)
						break;
					if (rlf[j]==lf[j])
						print(blankline);
					else
						print(s[j].substring(rlf[j], lf[j]) + linefix);
					rlf[j] = lf[j]+1;
				}
				print("\n");
			} while (lf[0]>=0);
		}
	}

	public static String getCalendarString(int year, int month) {
		int i;
		int weekfix = LocalDate.of(year, month, 1).getDayOfWeek().getValue()%7;
		--month;
		days_of_month[1] = 28 + leap(year);
		StringBuilder str = new StringBuilder(" 日 一 二 三 四 五 六\n");
		for (i=0; i<weekfix; i++)
			str.append("   ");
		for (i=1; i<=days_of_month[month]; i++) {
			str.append(String.format("%3d", i));
			if ((i+weekfix)%7 == 0)
				str.append('\n');
		}
		while (((i++)+weekfix)%7 != 0 )
			str.append("   ");
		str.append("   ");
	//	if ((--i+weekfix)%7 != 0)
			str.append('\n');
		str.append('\n');
		return str.toString();
	}

	private static int leap(int year) {
		return year%4==0 && year%100!=0 ? 1 : (year%400==0 ? 1 : 0);
	}
	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
