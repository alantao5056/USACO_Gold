import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

/*
 * This is has the same concept as the Sort
 * however, I used prefix sum to compute the number of switches
 * I imagined the corresponding indecies as intervals
 * and so I added one at the start of the intervals and
 * subtracted one at the end of intervals
 * then create a prefix sum based on that
 * to get final result
*/

public class Sort2 {
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
    
    int[] prefix = new int[N+2];
    for (int i = 0; i < N; i++) {
      prefix[Math.min(i, arr[i].sortIdx)+1]++;
      prefix[Math.max(i, arr[i].sortIdx)+1]--;
    }

    int result = 0;
    int cur = 0;
    for (int i = 1; i <= N; i++) {
      cur += prefix[i];
      result = Math.max(result, cur);
    }

    pw.println(result/2);

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