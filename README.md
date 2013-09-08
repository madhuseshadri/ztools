ztools
======

Missing but useful shell and c things

#1 - check.c

If you are on 64-bit x86 linux, you can simply copy from ztools/bin/* /usr/local/bin/* <br>

If you often use test -f this; then, test -eq, test -z, test -n and tired of remembering what -n, -z are, 
you can use check in place of test but say 

if check something is something; then ...<br>
if check something is not something; then ...<br> 
if check something is greater than something; then ..<br> 
if check something is lesser than something; then ..<br>
if check something is greater than or equal to something; then ..<br> 
if check something is lesser than or equal to something; then ..<br>
if check something is in something; then .. <br>
if check something is not in something; then .. <br>

try testcheck script which will do all the tests .. <br>

To do check needs file to be incorporated like test .. no -f, instead we say <br>
if check something is file; then <br>
if check something is executable; then<br> 
if check something is dir; then <br>
if check something is blockfile; then<br> 
if check something is charfile; then .. and so on ..<br> 

#2- slice.c <br>

you are sed / awk guru, there is absolutely no need for this silly little tool but if you like slice sentences, you may like this.  

I like python syntax [0:1] as we are on shell we don't need the square brackets <br>

slice something 0:2 result: so <br>
slice something 0:-2 result: somethi .. I think <br>
slice something -2:0 result: ng .. I think check it yourself ..<br> 

slice something - s o m e t h i n g <br>
slice "something-something-something" - results something something something <br>

that's slice and check .. <br>

shell tools<br>

#1 - rls <br>

There is ls -R but the recursive listing is not useful for simple piping, so we have rls which does the same 

#2 - mgrep <br>

search anything across anything in your hard drive or others .. <br>

so, if you want your desktop searched completely  <br>

mgrep regexpattern / <br>

There are few more .. check it out ..



