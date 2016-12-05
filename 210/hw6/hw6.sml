(* Alex McnUlin *)
(* CS 210 *)
(* HW6 *)
(* 12/04/16 *)

val argv = CommandLine.arguments()
val outfile = TextIO.openOut("mcnu5088.txt")
(* print my username to the file *)
val _ = TextIO.output(outfile, "mcnu5088\n")

(* Output the first element of the given list into the given file, then run the 
* function recursively on the rest of the list, and print my name as the last
* thing *)
fun printArgs [] = TextIO.output(outfile, "mcnu5088\n")
	| printArgs (myList) = (TextIO.output(outfile, hd(myList) ^ "\n"); printArgs(tl(myList)))

val _ = printArgs(argv)
val _ = TextIO.closeOut(outfile)
val _ = OS.Process.exit(OS.Process.success);
