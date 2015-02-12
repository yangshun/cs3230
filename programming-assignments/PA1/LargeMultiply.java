// CS3230-PA1-ABC
// Multiplication of 2 n-digit integers.
// Naive O(n^2) multiplication algorithm (Long Multiplication)
// Name:
// Date: 

import java.io.*;
import java.util.*;


class LargeMultiply { // in Mooshak online judge, make sure that Java file name = class name that contains Main method

    public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
        PrintWriter pw =  new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out))); // use this (a much faster output routine) instead of Java System.out.println (slow)

		int maxDigits =  20000; 

        int T, B;
		int[] arrV, arrM;
		arrV = new int[maxDigits+1];
		arrM = new int[maxDigits+1];
		String V,M; 

        T = sc.nextInt();
		
        for (int i = 1; i <= T; ++i) {
            B = sc.nextInt();
			sc.nextLine();
			V = sc.nextLine(); M = sc.nextLine();

			int fpV = scanArray(V, arrV);
			int fpM = scanArray(M, arrM);

			int[] result = new int[maxDigits*2];
            int resultLength = multArrays(arrV, arrM, arrV[arrV.length-1], arrM[arrM.length-1], B, result);

			String out = resultToString(result, resultLength, fpV+fpM);

			pw.write(trimZeros(out));
			pw.write("\n");
        }
        pw.close(); // do not forget to use this

    }

	private static int multArrays(int[] arrV, int[] arrM, int sizeV, int sizeM, int base, int[] result) {
		int d=0;
        int i=0;
        for (d=0; d<sizeM; d++) {
			int carry = 0;
			for (i=0; i<sizeV; i++) {
				result[i+d] += arrV[i] * arrM[d] + carry;
                carry = result[i+d] / base;
                result[i+d] %= base;
			}
            result[d+i] += carry;
		}
        return d+i;
	}
	

	private static String resultToString(int[] array, int size, int fp) {
		StringBuilder sb = new StringBuilder(size+1);
        fp -= 1;
        for (int i=size-1; i>=0; --i) {
            if (i == fp) {
				sb.append('.');
            }
			sb.append(toDigit(array[i]));
        }

		return sb.toString();
	}


	private static int scanArray(String s, int[] arr) {
		int index = 0;
		int fixedPoint = 0;
		for (int i=s.length()-1; i>=0; --i) {
			if (s.charAt(i) == '.') {
				fixedPoint = index;
			} else {
				arr[index] = parseDigit(s.charAt(i));
				index++;
			}
		}

		arr[arr.length-1] = index; // Store size.
		return fixedPoint;
	}


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

    
	private static int parseDigit(char c) {
		if (c <= '9') {
			return c - '0';
		} 
		return c - 'A' + 10;
	}
	

	private static char toDigit(int digit) {
		if (digit <= 9) {
			return (char)(digit + '0');
		} 
		return (char)(digit - 10 + 'A');
	}
}
