public class t4{
	public static void main(String[] args) {
		String s =
 " ======      =       =       =       =       \n"
+"   =       =   =      =     =      =   =     \n"
+"=  =      =  =   =     =   =      =  =  =    \n"
+" = =     =        =      =       =       =   \n";

		System.out.println( s.replace("=", "".format("%c", 0x1d307)) );
	}
}
