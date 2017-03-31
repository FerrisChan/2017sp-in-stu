while True:
    s = raw_input("Please enter 3 integers to combine a triangle(enter q to quit):")
    S = s.split(',')
    if s == 'q':
        break
    else:
        a=int(S[0])
        b=int(S[1])
        c=int(S[2])
        if a+b>c and a+c>b and b+c>a:
            if a==b and b==c:
                print ('It is a regular triangle.')
            else:
                if a==b or b==c or a==c:
                    print ('It is an isosceles triangle.')
                else:
                    print ('It is a normal triangle.')
        else:
            print ('Sorry, the 3 numbers cannot combine a triangle.')
         
print ('The end.')
