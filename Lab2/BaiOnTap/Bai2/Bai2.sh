echo Nhap ho ten
read Fullname
mkdir "$Fullname"

for name in $(cat monhoc.txt); do
    mkdir "$Fullname/$name"
done
exit 0