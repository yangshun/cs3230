/**
 *  This is a Java template for CS3230 - Programming Assignment 1 - Part 1
 *  (January-2015)
 *
 *  You are not required to follow the template. Feel free to modify any part.
 *
 *  Comment your code!
 */


import java.io.*;
import java.util.*;


class Template { // in Mooshak online judge, make sure that Java file name = class name that contains Main method
    public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out))); // use this (a much faster output routine) instead of Java System.out.println (slow)
        
        int T, B;
		String V, M; 
        T = sc.nextInt();
		
        for (int i = 1; i <= T; ++i) {
            B = sc.nextInt();
			sc.nextLine();
			V = sc.nextLine(); M = sc.nextLine();
			
			// Insert solution here.
			String P = "0000.00123ABC000"; // example output
			
			
			
			pw.write(trimZeros(P));
			pw.write("\n");
        }
        pw.close(); // do not forget to use this
    }
	
	
	/**
	 * Use to trim leading and trailing zeros on a result string.
	 */
	private static String trimZeros(String input) {
		int left = 0;
		int right = input.length()-1;
		int fp = input.indexOf('.');
		if (fp == -1) {
			fp = input.length();
		}
		
		while(left < fp-1) {
			if (input.charAt(left) != '0')
				break;
			left++;
		}
		
		while (right >= fp) {
			if (input.charAt(right) != '0') {
				if (input.charAt(right) == '.')
					right--;
				break;
			}
			right--;
		}
		
		if (left >= fp)
			return "0" + input.substring(left,right+1);
		return input.substring(left,right+1);
	}
    
	/**
	 * Convert digit to int (for reading)
	 */
	private static int parseDigit(char c) {
		if (c <= '9') {
			return c - '0';
		} 
		return c - 'A' + 10;
	}
	
	/**
	 * Convert int to digit. (for printing)
	 */
	private static char toDigit(int digit) {
		if (digit <= 9) {
			return (char)(digit + '0');
		} 
		return (char)(digit - 10 + 'A');
	}
}
