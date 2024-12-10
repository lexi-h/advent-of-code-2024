grep -E -o 'mul[(][[:digit:]]+[,][[:digit:]]+[)]' input-raw > input-clean
grep -E -o '[[:digit:]]+,[[:digit:]]+' input-clean > input-final
