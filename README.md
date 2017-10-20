
## Data Types

Integers and Array of Integers.

```fortran
int data, array[100];
int sum;
```

All the variables have to be declared in the declblock{....} before being used
in the codeblock{...}. Multiple variables can be declared in the statement 
and each declaration statement ends with a semi-colon. 

## Expressions


## `for` loop

```fortran
for i = 1, 100 {
	.....
}

for i = 1, 100, 2 {
	.....
}
```

## `if-else` statement

```fortran
	if expression {
	....
	}
	....

	if expression {
	...
	}
	else {
	....
	}
```

## `while` statment

```fortran
	while expression {

	}

```

## conditional and unconditional `goto`

```fortran
	got label

	goto label if expression
```

## print/read

```fortran
	print "blah...blah", val
	println "new line at the end"
	read sum
	read data[i]
```
