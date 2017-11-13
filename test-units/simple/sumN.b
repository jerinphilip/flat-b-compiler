declblock{
	int data[100];
	int i, sum;
}

codeblock{
	for i = 0, 100 {
		data[i] = i;
	}
	

	sum = 0;
	for i = 0, 100 {
		sum = sum + data[i];
 	}

	print "Sum value: ", sum;

}

