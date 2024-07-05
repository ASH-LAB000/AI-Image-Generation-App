L = list(map(int, input().split()))
l = 0
r = len(L)-1
flag = 0
while (l <= r):
  mid = (l+r)//2
  
  if (L[mid] == 1 and (mid == 0 or L[mid - 1] == 0)):
    print(mid)
    flag = 1
    break
     
  elif (L[mid] == 1):
    r = mid - 1
  else:
    l = mid + 1
if flag==0:
  print(-1)