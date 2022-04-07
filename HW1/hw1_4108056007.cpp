#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	FILE *fp;
	int black=0, white=0;
	char c, name[500]="", pre='2';
	float first_entropy=0, second_entropy=0, diff_entropy=0, all;
	
	fp = fopen("avatar.txt", "r"); //open file
	if(fp==NULL) printf("error to open the file\n");
	
	int black_white=0, black_black=0, white_white=0, white_black=0;
	while ((c = getc(fp)) != EOF){
		if(c=='0') black++;
		else white++;
		
		if(pre=='0' && c=='1'){ //黑色後面接白色，diff= 1-0= 1 
			black_white++;
		}
		else if(pre=='0' && c=='0'){ //黑色後面接黑色， diff= 0-0= 0
			black_black++;
		}
		else if(pre=='1' && c=='0'){ //白色後面接黑色， diff= 0-1= -1
			white_black++;
		}
		else if(pre=='1' && c=='1'){ //黑色後面接白色， diff= 1-1= 0
			white_white++;
		}
		pre = c;
	}
	
	float p_b= ((float)black/(float)(black+white)); //P(b)
	float p_w= ((float)white/(float)(black+white)); //P(w)
	float p_wb= ((float)black_white/(float)(black_white+black_black)); // P(w|b)
	float p_bw= ((float)white_black/(float)(white_black+white_white)); // P(b|w)
	float p_bb= ((float)black_black/(float)(black_white+black_black)); // P(b|b)
	float p_ww= ((float)white_white/(float)(white_black+white_white)); // P(w|w)
	
	printf("Number of Blacks= %d, Whites= %d\n", black, white);
	printf("P(b)= %f, P(w)= %f\n", p_b, p_w);
	printf("P(w|w)= %f, P(w|b)= %f, P(b|w)=%f, P(b|b)=%f\n\n", p_ww, p_wb, p_bw, p_bb);
	
	float h_b= ((-1)*((p_bb*log2(p_bb))+(p_wb*log2(p_wb)))); //H(b)= -P(w|b)*log2(P(w|b))-P(b|b)*log2(P(w|b))
	float h_w= ((-1)*((p_bw*log2(p_bw))+(p_ww*log2(p_ww)))); //H(w)= -P(w|w)*log2(P(w|w))-P(b|w)*log2(P(w|w))
	
	first_entropy = ((-1)*((p_b*log2(p_b))+(p_w*log2(p_w)))); //H= -P(b)log2(P(b))-P(w)log2(P(w))
	second_entropy = ((p_b*h_b)+(p_w*h_w)); //H= P(b)*H(b)+P(w)*H(w)
	
	printf("First entropy= %f, Second entropy= %f\n\n", first_entropy, second_entropy);
	printf("-----------------------------------------------\n\n");
	
	float neg_one, one, zero;
	all= (float)(black_white+black_black+white_black+white_white);
	
	printf("Number of differences: \n");
	printf("Negative one= %d, One= %d, Zero= %d\n\n", white_black, black_white, (black_black+white_white));
	printf("Entropy of differences between neighboring pixels:\n");
	neg_one = ((float)white_black/all); // P(-1)
	one = ((float)black_white/all); // P(1)
	zero = ((float)(black_black+white_white)/all); //P(0)
	printf("P(-1)= %f, P(1)= %f, P(0)= %f\n\n", neg_one, one, zero);
	
	diff_entropy = (-1)*((neg_one*log2(neg_one)) + (one*log2(one)) + (zero*log2(zero)));
	printf("Diff entropy= %f\n", diff_entropy);
	
	fclose(fp);
	return 0;
}



