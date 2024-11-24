Name="huenguyen"
ID="1063"

echo Nhap name
read name
echo MSSV
read id

if [ $Name = $name ] && [ $ID = $id ]; then
    echo "Chao"
else
    echo "Access denied"
fi


# while [ $Name != $name ] || [ $ID != $id ]; do
#     echo Nhap name
#     read name
#     echo MSSV
#     read id
# done

for var in 0 1 2 3 4
do
echo Nhap name
read name
echo MSSV
read id
done