import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

/*
 * After getting the hint of splitting the array in
 * two and then trying to see how many times it takes to switch it,
 * I came up with a simple for loop to solve the problem. 
 * First, I got the sorted indexes and normal indexes
 * then everytime I cycled through I broke the situation into different cases
 * and modified count each time and recorded a maxCount. 
*/

public class Sort {
  static StreamTokenizer st;
  static int N;

  static class Node {
    int val;
    int sortIdx;
    int temp;
    boolean visited = false;
    public Node(int val) {
      this.val = val;
    }
  }

  public static void main(String[] args) throws Exception {
    // read input
    BufferedReader br = new BufferedReader(new FileReader("sort.in"));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    st = new StreamTokenizer(br);
    PrintWriter pw = new PrintWriter(new File("sort.out"));
    // PrintWriter pw = new PrintWriter(System.out);
    N = nextInt();
    
    // solve
    Node[] arr = new Node[N];
    Node[] arr2 = new Node[N];
    for (int i = 0; i < N; i++) {
      arr[i] = new Node(nextInt());
      arr[i].temp = i;
      arr2[i] = arr[i];
    }

    Arrays.sort(arr2, new Comparator<Node>() {
      @Override
      public int compare(Node a, Node b) {
        if (a.val == b.val) {
          return a.temp - b.temp;
        }
        return a.val - b.val;
      }
    });

    for (int i = 0; i < N; i++) {
      arr2[i].sortIdx = i;
    }
    boolean sorted = true;
    for (int i = 0; i < N; i++) {
      if (i != arr[i].sortIdx) {
        sorted = false;
      }
    }

    if (sorted) {
      pw.println(1);
      br.close();
      pw.close();
      return;
    }

    int count = 0;
    int maxCount = 0;

    for (int i = 0; i < N; i++) {
      if (arr[i].sortIdx == arr[i].temp) continue;
      boolean one = !arr2[i].visited;
      boolean two = arr[i].sortIdx >= i;
      if (one && two) {
        count++;
      } else if (one && !two) {
        //count++; //?
      } else if (!one && !two) {
        count--;
      } else { // !one && two
        // count--;
      }

      arr[i].visited = true;
      maxCount = Math.max(count, maxCount);
    }

    pw.println(maxCount);

    br.close();
    pw.close();
  }

  private static int nextInt() throws Exception {
    st.nextToken();
    return (int) st.nval;
  }

  private static String nextString() throws Exception {
    st.nextToken();
    return st.sval;
  }
}