(* Matthew Waltz (walt2909) *)
val out = TextIO.openOut("walt2909.txt")
val _ = TextIO.output (out, "walt2909\n")
 
fun splitout [] = TextIO.output (out, "walt2909\n")
|   splitout (x::xs) = (TextIO.output (out, x); splitout xs)
 
val args = CommandLine.arguments()
val _ = splitout args
 
val _ = TextIO.closeOut out
val _ = OS.Process.exit(OS.Process.success)
