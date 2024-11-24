salutation="hello"
echo $salutation
echo "The program $0 is now running"
echo "The second parameter was $2"
echo "The first parameter was $1"
echo "The paramater list was $*"

#echo "The parameter list as a single string $*"
#echo "The parameter list as a separate words $@"

echo "The user's home directory is $HOME"


echo "Please enter a new greeting"
read salutation

echo  $salutation
echo "The script is now complete"


exit 0