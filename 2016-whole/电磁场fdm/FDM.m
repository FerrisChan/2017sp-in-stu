%% FDM
nx=5, ny =5;
v1= ones(ny,nx);
v1(1,:)= ones(1,nx)*100;
v1([2:end],:)= ones(ny-1,nx)*0;
k= 0;
w= 0.0001;
z= 0;
while z~=1;
    for i = 2:ny-1
        for j= 2:ny-1
            v2(i,j) = (v1(i-1,j)+v1(i,j-1)+v1(i,j+1)+v1(i+1,j))/4;
            t(i,j) = abs(v1(i,j)-v2(i,j));
            v1(i,j) = v2(i,j);
        end
    end
    t;
    x=t < w;
    y = all(x);
    z = all(y);
    k = k+1;
end
