class FenwickTree:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)
    
    def add(self, idx, value):
        while idx <= self.size:
            self.tree[idx] += value
            idx += idx & -idx
    
    def sum(self, idx):
        s = 0
        while idx > 0:
            s += self.tree[idx]
            idx -= idx & -idx
        return s
    
    def range_sum(self, left, right):
        return self.sum(right) - self.sum(left - 1)

import sys
input = sys.stdin.read
data = input().split()

n = int(data[0])
q = int(data[1])

# Reading initial salaries
salaries = list(map(int, data[2:2+n]))

# Reading queries
queries = data[2+n:]

# Fenwick Tree for frequencies
MAX_SALARY = 10**9
BIT = FenwickTree(MAX_SALARY)

# Initialize BIT with initial salaries
for i in range(1, n+1):
    BIT.add(salaries[i-1], 1)

index = 0
output = []

# Processing each query
while index < len(queries):
    if queries[index] == '!':
        k = int(queries[index+1])
        x = int(queries[index+2])
        old_salary = salaries[k-1]
        salaries[k-1] = x
        BIT.add(old_salary, -1)
        BIT.add(x, 1)
        index += 3
    elif queries[index] == '?':
        a = int(queries[index+1])
        b = int(queries[index+2])
        result = BIT.range_sum(a, b)
        output.append(result)
        index += 3

# Print all results for ? queries
for result in output:
    print(result)
