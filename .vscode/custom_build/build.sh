headers=$(find -type d)

includes=""

for head in $headers
do
  includes="$includes -I$head"
done

args=""
if [ $1 = "RELEASE" ]
then
  args="-o out-release -O3"
else
  args="-o out-debug"
fi

echo "/usr/bin/g++ -std=c++2a -g $includes -L./lib $(find -type f -name '*.cpp') -lglfw -lGLEW -lGL -D $1 $args"
/usr/bin/g++ -std=c++2a -g $includes -L./lib $(find -type f -name '*.cpp') -lglfw -lGLEW -lGL -D $1 $args
return_code=$?

return return_code