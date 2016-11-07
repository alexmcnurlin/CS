#! /usr/bin/env perl

use strict;
use File::Compare;
use File::Copy;
use File::Path;

sub main {
    my $file = shift(@_);
    -e $file or die("Error: \"$file\" does not exist");

    my $dir = get_round_dir(); # Finds the directory to move files to

    # Checks for files of the same name, and renames the file accordingly
    my $newfile = $file;

    #print(compare($file, "$dir/$file.blah"));
    if ( -e "$dir/$file" && compare("$file", "$dir/$file")) {
        my $suffix = 1;
        while ( -e "$dir/$file.$suffix") {
            $suffix++;
        }
        $newfile = "$newfile.$suffix";
    } elsif (!compare("$file", "$dir/$file")) {
        print("\"$file\" already exists in roundfile. Would you like to overwrite it? [y/n]: ");
        my $u = uc(<STDIN>);
        chomp($u);
        if ($u eq "Y" || $u eq "YES") {
            # pass
        } elsif ($u eq "N" || $u eq "NO") {
            print("Didn't remove \"$file\"\n");
            return(1);
        } else {
            main("$file");
            return(1);
        }
    }

    move("$file", "$dir/$newfile");
}

sub empty {
    my $dir = get_round_dir();
    if ( -e $dir ) {
        unlink(glob("$dir/*"));
        rmtree(glob("$dir/*/"));
    }
}

sub flush {
    my $dir = get_round_dir();
    if ( -e $dir ) {
        rmtree("$dir");
        print("Removing $dir\n");
    }
}

# Asks the user if they want to remove the given file
#   if yes, runs main($file). If anything else, do nothing
sub interactive {
    my $file = shift(@_);
    print("Are you sure you want to remove \"$file\"? [y/n]: ");
    my $u = uc(<STDIN>);
    chomp($u);
    if ($u eq "Y" || $u eq "YES") {
        main("$file");
    } elsif ($u eq "N" || $u eq "NO") {
        print("Didn't remove \"$file\"\n");
    } else {
        interactive("$file");
        return(1);
    }
}

# Lists all files in the roundfile directory
sub list {
    my $dir = get_round_dir();
    system("ls -l $dir");
}

sub retrieve {
    my $file = shift(@_);

    my $dir = get_round_dir();

    # Check  if the file exists with the roundfile directory
    -e "$dir/$file" or die("$dir/$file does not exist!");

    if (-e "$file") {
        print("$file already exists in the current directory. Do you want to overwrite it? [y/n]: ");
        my $u = uc(<STDIN>);
        chomp($u);
        if ($u eq "N" || $u eq "NO") {
            print("Didn't retrieve \"$file\"\n");
            return(1);
        } elsif ($u eq "Y" || $u eq "YES") {
            #pass
        } else {
            retrieve($file)
        }
    }

    copy("$dir/$file", "$file");
}

# Returns the path to the roundfile directory. if 'roundfile' exists in the 
#   current directory, returns that. Otherwise return ~/roundfile. Creates
#   '~/roundfile' if it doesn't exist
sub get_round_dir {
    my $dir;
    if (-e "./roundfile" && -d "./roundfile") {
        $dir = "./roundfile";
    } else {
        $dir = $ENV{"HOME"}."/roundfile";
    }

    if (! -e "$dir") {
      mkdir("$dir") or die("Unable to make directory $$ENV{'HOME'}/roundfile\n");
      print("$dir does not exist. Creating it...\n");
    }

    return("$dir");
}

#for my $arg (@ARGV) {
# Loop over every argument
for (my $i=0; $i<scalar(@ARGV); $i++) {
    my $arg = $ARGV[$i];

    # Check if the given arg is an option
    if (substr($arg, 0, 1) eq "-") {
        my @opts = split(//, $arg);

        # Loop through each argument
        for (my $j=1; $j<scalar(@opts); $j++) {
            # Check each command line argument
            if ($opts[$j] eq "e") {
                empty();
            } elsif ($opts[$j] eq "f") {
                flush();
            } elsif ($opts[$j] eq "i") {
                # Run the interactive function if it is the last option in the group
                #   and the next arg exists
                if ($j+1 == scalar(@opts) && $ARGV[$i+1] && substr($ARGV[$i+1],0,1) ne "-") {
                    interactive($ARGV[$i+1]);
                    $i++;
                } else {
                    die("Error: Option 'i' requires additional argument...\n");
                }
            } elsif ($opts[$j] eq "l") {
                list();
            } elsif ($opts[$j] eq "r") {
                # Run the retrieve function if it is the last option in the group
                #   and the next arg exists
                if ($j+1 == scalar(@opts) && $ARGV[$i+1] && substr($ARGV[$i+1],0,1) ne "-") {
                    retrieve($ARGV[$i+1]);
                    $i++;
                } else {
                    die("Error: Option 'r' requires additional argument...$ARGV[$i+1]\n");
                }
            } else {
                print("Error: Option '$opts[$j]' is not a valid option\n");
            }
        }

    } else {
        main($arg);
    }
}
