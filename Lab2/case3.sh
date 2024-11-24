echo  "Is it morninng? Please answer yes or no: "
read timeofday

case "$timeofday" in
    "yes" | "Yes" | "y" | "YES")     
        echo "Good Morning"
        echo "Up bright and early morning";;
    [nN]* )     
        echo "Good Afternoon";;
    "*"  )     echo "Sorry, answer not recognized."
esac
exit 0