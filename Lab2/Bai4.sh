echo Nhap chuoi
read string

if grep -l "$string" "test.txt"; then 
    echo chuoi "$string" ton tai trong file test.txt
else
     echo chuoi "$string" khong ton tai trong file test.txt
fi 

exit 0