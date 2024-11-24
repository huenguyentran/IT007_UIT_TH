count=0
for filename in ../../../OS_LAB2_IMG/*; do
    if [[ "$filename" == *.jpg ]]; then
        count=$((count + 1))
        mv $filename ../../../JPG/
    fi
done
echo So luong file JPG la $count
exit 0