import java.util.Scanner;
import java.time.LocalDate;

public class xx1{
	public static void main(String[] args) throws java.io.IOException{
		int i, j, year=666, weekfix;

		println("请输入一个年份:");
		Scanner scan = new Scanner(System.in);
		for (;;)
			if (scan.hasNextInt()) {
				year = scan.nextInt();
				if (year>0)
					break;
			}
			else
				scan.nextLine();
		weekfix = LocalDate.of(year, 1, 1).getDayOfWeek().ordinal()+1;
		month[1] += leap(year);
		printf(" %d年\n", year);
		for (i=0; i<12; i++) {
			printf("%2d月\n", i+1);
			println(" 日 一 二 三 四 五 六");
			for (j=0; j<weekfix; j++)
				print("   ");
			for (j=1; j<=month[i]; j++) {
				printf("%3d", j);
				if ((j+weekfix)%7==0)
					print("\n");
			}
			if ((--j+weekfix)%7!=0)
				print("\n");
			print("\n");
			weekfix = (weekfix+month[i])%7;
		}
	}

	private static int leap(int year) {
		return year%4==0 && year%100!=0 ? 1 : (year%400==0 ? 1 : 0);
	}
	private static int month[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	private static void print(String s) {System.out.print(s);}
	private static void println(String s) {System.out.println(s);}
	private static void printf(String fmt, Object... args) {System.out.printf(fmt, args);}
}
