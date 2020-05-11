package examprep;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Regex {
  public static final String EXPRESSION = 
		  "^[A-Z][a-zA-Z0-9]{1,24}$";
      //"\\A(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}\\z";
  
  public static void main(String[] args) {
    BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("Please input now: ");
    String input;
    Pattern pattern = Pattern.compile(EXPRESSION);
    try {
      input = read.readLine();
   
      while (!input.equals("exit")) {
        
        Matcher matcher = pattern.matcher(input);
        
        if (matcher.matches()) {
          System.out.println(input + " matches pattern " + EXPRESSION);
        } else {
          System.out.println(input + " does not match " + EXPRESSION);
        }
        System.out.println("Please input ");
        input = read.readLine();
      }
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }
}
