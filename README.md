ztools
======

Missing but useful shell and c things

check.c - copy bin / check from *bin/ to your bin

If you often use test -f this; then, test -eq, test -z, test -n and tired of remembering what -n, -z are, 
you can use check in place of test but say 

if check something is something; then ...
if check something is not something; then ... 
if check something is greater than something; then .. 
if check something is lesser than something; then ..
if check something is greater than or equal to something; then .. 
if check something is lesser than or equal to something; then ..
if check something is in something; then .. 
if check something is not in something; then .. 

try testcheck script which will do all the tests .. 

check needs file to be incorporated like test .. no -f, instead we say
if check something is file; then 
if check something is executable; then 
if check something is dir; then 
if check something is blockfile; then 
if check something is charfile; then .. and so on .. 

slice.c 
you are sed / awk guru, there is absolutely no need for this silly little tool but if you like slice sentences, 
uses python syntax without [0:1] but not the square brackets

slice something 0:2 - so 
slice something 0:-2 - somethi .. I think 
slice something -2:0 - ng .. I think check it yourself .. 

slice something - s o m e t h i n g 
slice "something-something-something" - results something something something 

that's slice and check .. 

shell tools

There is ls -al R but the recurse listing is not useful for piping, so I have rls which does that same 
mgrep searches across anything .. 

so, if you want your desktop searched completely 

mgrep regexpattern /



