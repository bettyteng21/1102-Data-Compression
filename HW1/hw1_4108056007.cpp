#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	FILE *fp;
	float black=0, white=0;
	char c, name[500]="", pre='2', pre2='2';
	float iid_entropy=0, first_entropy=0, second_entropy=0, diff_entropy=0, all;
	
	fp = fopen("avatar.txt", "r"); //open file
	if(fp==NULL) printf("error to open the file\n");
	
	float bw=0, wb=0, bb=0, ww=0, wbw=0, wbb=0, www=0, wwb=0, bbw=0, bbb=0, bww=0, bwb=0;
	while ((c = getc(fp)) != EOF){
		if(c=='0') black++;
		else white++;
		
		if(pre2=='0'){
			if(pre=='0' && c=='1'){ //黑色後面接白色，diff= 1-0= 1 
				bbw++; bw++;
			}
			else if(pre=='0' && c=='0'){ //黑色後面接黑色， diff= 0-0= 0
				bbb++; bb++;
			}
			else if(pre=='1' && c=='0'){ //白色後面接黑色， diff= 0-1= -1
				bwb++; wb++;
			}
			else if(pre=='1' && c=='1'){ //黑色後面接白色， diff= 1-1= 0
				bww++; ww++;
			}
		}
		else if(pre2=='1'){
			if(pre=='0' && c=='1'){ //黑色後面接白色，diff= 1-0= 1 
				wbw++; bw++;
			}
			else if(pre=='0' && c=='0'){ //黑色後面接黑色， diff= 0-0= 0
				wbb++; bb++;
			}
			else if(pre=='1' && c=='0'){ //白色後面接黑色， diff= 0-1= -1
				wwb++; wb++;
			}
			else if(pre=='1' && c=='1'){ //黑色後面接白色， diff= 1-1= 0
				www++; ww++;
			}
		}
		else{
			if(pre=='0' && c=='1'){ //黑色後面接白色，diff= 1-0= 1 
				bw++;
			}
			else if(pre=='0' && c=='0'){ //黑色後面接黑色， diff= 0-0= 0
				bb++;
			}
			else if(pre=='1' && c=='0'){ //白色後面接黑色， diff= 0-1= -1
				wb++;
			}
			else if(pre=='1' && c=='1'){ //黑色後面接白色， diff= 1-1= 0
				ww++;
			}
		}
		
		pre2 = pre;
		pre = c;
	}
	
	float p_b, p_w, p_wb, p_bw, p_bb, p_ww, p_wbw, p_wbb, p_www, p_wwb, p_bbw, p_bbb, p_bww, p_bwb;
	float h_b, h_w, h_bb, h_ww, h_wb, h_bw;
	
	p_b= (black/(black+white)); //P(b)
	p_w= (white/(black+white)); //P(w)
	p_wb= (bw/(bw+bb)); // P(w|b)
	p_bw= (wb/(wb+ww)); // P(b|w)
	p_bb= (bb/(bw+bb)); // P(b|b)
	p_ww= (ww/(wb+ww)); // P(w|w)
	p_wbw= (bww/(bwb+bww));  p_bbw= (bwb/(bwb+bww));
	p_wbb= (bbw/(bbb+bbw));  p_bbb= (bbb/(bbb+bbw));
	p_www= (www/(wwb+www));  p_bww= (wwb/(www+wwb));
	p_wwb= (wbw/(wbw+wbb));  p_bwb= (wbb/(wbb+wbw)); // P(b|wb)
	
	
	printf("Number of Blacks= %d, Whites= %d\n", (int)black, (int)white);
	printf("P(b)= %f, P(w)= %f\n", p_b, p_w);
	printf("P(w|w)= %f, P(w|b)= %f, P(b|w)=%f, P(b|b)=%f\n", p_ww, p_wb, p_bw, p_bb);
	printf("P(w|wb)= %f, P(w|bw)= %f, P(w|ww)=%f, P(w|bb)=%f\n", p_wwb, p_wbw, p_www, p_wbb);
	printf("P(b|wb)= %f, P(b|bw)= %f, P(b|ww)=%f, P(b|bb)=%f\n\n", p_bwb, p_bbw, p_bww, p_bbb);
	
	h_b= ((-1)*((p_bb*log2(p_bb))+(p_wb*log2(p_wb)))); //H(b)= -P(w|b)*log2(P(w|b))-P(b|b)*log2(P(w|b))
	h_w= ((-1)*((p_bw*log2(p_bw))+(p_ww*log2(p_ww)))); //H(w)= -P(w|w)*log2(P(w|w))-P(b|w)*log2(P(w|w))
	h_bb= ((-1)*((p_wbb*log2(p_wbb))+(p_bbb*log2(p_bbb))));
	h_ww= ((-1)*((p_www*log2(p_www))+(p_bww*log2(p_bww))));
	h_wb= ((-1)*((p_wwb*log2(p_wwb))+(p_bwb*log2(p_bwb)))); 
	h_bw= ((-1)*((p_wbw*log2(p_wbw))+(p_bbw*log2(p_bbw)))); //發生bw情況下的H 
	
	iid_entropy = ((-1)*((p_b*log2(p_b))+(p_w*log2(p_w)))); //H= -P(b)log2(P(b))-P(w)log2(P(w))
	first_entropy = ((p_b*h_b)+(p_w*h_w)); //H= P(b)*H(b)+P(w)*H(w)
	second_entropy = (p_bb*p_b*h_bb)+(p_ww*p_w*h_ww)+(p_wb*p_b*h_bw)+(p_bw*p_w*h_wb);
	
	printf("iid entropy= %f, first entropy= %f, second entropy= %f\n\n", iid_entropy, first_entropy, second_entropy);
	printf("-----------------------------------------------\n\n");
	
	float neg_one, one, zero;
	all= (bw+bb+wb+ww);
	
	printf("Number of differences: \n");
	printf("Negative one= %d, One= %d, Zero= %d\n\n", (int)wb, (int)bw, (int)(bb+ww));
	printf("Entropy of differences between neighboring pixels:\n");
	neg_one = (wb/all); // P(-1)
	one = (bw/all); // P(1)
	zero = ((bb+ww)/all); //P(0)
	printf("P(-1)= %f, P(1)= %f, P(0)= %f\n\n", neg_one, one, zero);
	
	diff_entropy = (-1)*((neg_one*log2(neg_one)) + (one*log2(one)) + (zero*log2(zero)));
	printf("Diff entropy= %f\n", diff_entropy);
	
	fclose(fp);
	return 0;
}



