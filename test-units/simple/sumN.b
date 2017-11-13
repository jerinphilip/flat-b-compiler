declblock{
	int data[100];
	int i, sum;
}

codeblock{
	for i = 0, 99 {
		data[i] = i;
	}
	

	sum = 0;
	for i = 0, 99 {
		sum = sum + data[i];
 	}

	println "Sum value (for): ", sum;

}

