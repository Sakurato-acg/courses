
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
public class dm {
	public static int len,p;
	public static String[] string = {"����","��ռ��"};
	public static List<storge> list = new LinkedList<storge>();
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		System.out.println("�������ʼ�ռ�Ĵ�С��");
		len = input.nextInt();
		System.out.println("������ѡ����㷨��1����FF��2����BF��3����WF");
		p = input.nextInt();
		list.add(new storge("NULL",0,len-1,len,0,p));
		while(true) {
			System.out.println("��������һ����Ҫ���еĲ���1�������䣬2�������գ�3�����˳���ǰ�㷨");
			int key = input.nextInt();
			switch (key) {
			case 1:
				System.out.println("����������ţ�������С");
				String name1 = input.next();
				int large = input.nextInt();
				allocation(name1,large);
				show();
				break;
			case 2:
				System.out.println("�����뽫Ҫ���յķ���");
				String name2 = input.next();
				release(name2);
				show();
				break;
			case 3:
				list.clear();
				System.out.println("�������ʼ�ռ�Ĵ�С��");
				len = input.nextInt();
				System.out.println("������ѡ����㷨��1����FF��2����BF��3����WF");
				p = input.nextInt();
				list.add(new storge("NULL",0,len-1,len,0,p));//���Ƚ���ʼ�ռ����
				break;
			default:
				System.out.println("��Ч����������������");
				break;
			}
		}
	}
	public static void release(String name) {
		boolean flag = false;
		int t = 0;
		List<storge> cop = new LinkedList<>();
		for (int j = 0; j < len; j++) {
			for (int i = 0; i < list.size(); i++) {
				storge temporacy = list.get(i);
				if (j == temporacy.start && temporacy.capacity!=0) {
					cop.add(temporacy);
				}
			}
		}
		list.clear();
		storge shu [] =new storge[cop.size()];
		for (int i = 0; i < cop.size(); i++) {
			shu[i] = cop.get(i);
		}
		for (int i = 0; i < cop.size(); i++) {
			if (shu[i].name.equals(name)) {
				if (i !=0  && i !=shu.length-1 ) {
					System.out.println("                            �м�");
					if (shu[i-1].status != 0 && shu[i+1].status != 0) {
						System.out.println("                            �м���һ��");
						shu[i].status = 0;
						shu[i].name = "NULL";
					}else {
						if (shu[i+1].status == 0) {
							System.out.println("                            �м��");
							shu[i].capacity = shu[i].capacity + shu[i+1].capacity;
							shu[i].end = shu[i].end + shu[i+1].capacity;
							shu[i].status = 0;
							shu[i].name = "NULL";
							shu[i+1].status = 0;
							shu[i+1].name = "-1";
						}
						if (shu[i-1].status == 0) {
							System.out.println("                            �м���");
							shu[i-1].capacity = shu[i-1].capacity + shu[i].capacity;
							shu[i-1].end = shu[i-1].end + shu[i].capacity;
							shu[i].status = 0;
							shu[i-1].name = "NULL";
							shu[i].name = "-1";
						}
					}
				}else if (i == 0 && i !=shu.length-1) {
					System.out.println("                            ��ͷ");
					if (shu[i+1].status == 0) {
						shu[i].capacity = shu[i].capacity + shu[i+1].capacity;
						shu[i].end = shu[i].end + shu[i+1].capacity;
						shu[i].status = 0;
						shu[i].name = "NULL";
						shu[i+1].name = "-1";
					}else {
						shu[i].status = 0;
						shu[i].name = "NULL";
					}
				}else if (i !=0 && i ==shu.length-1) {
					System.out.println("                            ��β");
					if (shu[i-1].status == 0) {
						shu[i-1].capacity = shu[i-1].capacity + shu[i].capacity;
						shu[i-1].end = shu[i-1].end + shu[i].capacity;
						shu[i].status = 0;
						shu[i-1].name = "NULL";
						shu[i].name = "-1";
					}else {
						shu[i].status = 0;
						shu[i].name = "NULL";
					}
				}
				flag = true;
			}	
		}
		list.clear();
		for (int j = 0; j < shu.length; j++) {
			if (!shu[j].name.equals("-1") && shu[j].capacity != 0) {
				list.add(shu[j]);
				System.out.println(shu[j].name);
			}
		}
		if (flag) {
			System.out.println("�ͷųɹ�");
		}else {
			System.out.println("�ͷ�ʧ�ܣ�û�д˷���");
		}
	}
	public static void allocation(String name,int large) {
		boolean falg = true;
		for(storge key:list) {
			if (key.name.equals(name)) {
				System.out.println(name+" �Ѿ�����,����ʧ�ܣ�");
				return;
			}
			if (key.capacity >= large) {
			falg = false;
			}
		}
		if (falg == true) {
			System.out.println("ʣ��ռ䲻�㣬����ʧ��");
			return;
		}
		if (p == 1) {
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < list.size(); j++) {
					storge tems = list.get(j);
					if (j == tems.start && tems.status == 0 && tems.capacity >= large) {
						list.add(new storge(name, tems.start, tems.start+large, large, 1,tems.algorithm));//��ʾ���ڽ���һ����������
						storge temp = new storge("NULL", tems.start+large, tems.end, tems.capacity-large, 0,tems.algorithm);
						list.remove(tems);
						list.add(temp);
						System.out.println("��������ɹ�");
						return;
					}
				}
			}
		}else if (p == 2) {
			int min = 10000;
			storge copy = new storge("", 1, 1, 1, 1, 2);
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < list.size(); j++) {
					storge tems = list.get(j);
					if (tems.status == 0 && tems.capacity >= large && tems.start == i) {
						if (tems.capacity < min) {
							min = tems.capacity;
							copy = tems;
						}
					}
				}
			}
			System.out.println(copy.start+" "+copy.name);
			list.add(new storge(name, copy.start, copy.start+large, large, 1,copy.algorithm));//��ʾ���ڽ���һ����������
			storge temp = new storge("NULL", copy.start+large, copy.end, copy.capacity-large, 0,copy.algorithm);
			list.remove(copy);
			list.add(temp);
			System.out.println("��������ɹ�");
			return;
		}else  if (p == 3) {
			int max = -10000;
			for (int i = 0; i < list.size(); i++) {
				System.out.println(list.get(i).name+"    "+list.get(i).capacity);
			}
			storge copy = new storge("", 1, 1, 1, 1, 3);
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < list.size(); j++) {
					storge tems = list.get(j);
					if (tems.status == 0 && tems.capacity >= large && tems.start == i) {
						if (tems.capacity > max) {
							max = tems.capacity;
							copy = tems;
						}
					}
				}
			}
			list.add(new storge(name, copy.start, copy.start+large, large, 1,copy.algorithm));//��ʾ���ڽ���һ����������
			storge temp = new storge("NULL", copy.start+large, copy.end, copy.capacity-large, 0,copy.algorithm);
			list.remove(copy);
			list.add(temp);
			System.out.println("��������ɹ�");
			return;
		}	
	}
	public static void show() {
		System.out.println("������\t\tʼַ\t\t��ַ\t\t��������\t\t����״̬\t\t");
		for (int j = 0; j < len; j++) {
			for (int i = 0; i < list.size(); i++) {
				storge temporacy = list.get(i);
				if (j == temporacy.start && temporacy.capacity!=0) {
					System.out.println(temporacy.name+"\t\t"+temporacy.start+"\t\t"+
							+temporacy.end+"\t\t"+temporacy.capacity+"\t\t"+string[temporacy.status]+"\t\t");
				}
			}
		}
	}
}

class storge {
	String name;
	int start;
	int end;
	int capacity;
	int status;
	int algorithm;
	public storge(String name,int start,int end, int capacity,int status,int algorithm) {
		super();
		this.name=name;
		this.start=start;
		this.end=end;
		this.capacity=capacity;
		this.status=status;
		this.algorithm=algorithm;
	}
}