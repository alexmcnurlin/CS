#! /usr/bin/env perl

use strict;
use File::Compare;
use File::Copy;
use File::Path;

sub main {
    my $file = shift(@_);
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
    }

    system("mv \"$file\" \"$dir/$newfile\"");
}

sub empty {
    my $dir = get_round_dir();
    if ( -e $dir ) {
        unlink(glob("$dir/*"));
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
    print("Are you sure you want to remove \"$file\": ");
    my $u = uc(<STDIN>);
    chomp($u);
    if ($u eq "Y" || $u eq "YES") {
        main("$file");
    } else {
        print("Didn't remove \"$file\"\n");
    }
}

# Lists all files in the roundfile directory
sub list {
    my $dir = get_round_dir();
    system("ls -l $dir");
}

sub retrieve {
    my $file = shift(@_);
    print("Retrieve: $file\n");
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
      mkdir("$dir") or die("Unable to make directory $$ENV{'HOME'}/roundfile");
      print("$dir does not exists. Creating it...\n");
    }

    return("$dir");
}

sub diff {
    my $file1 = shift(@_);
    my $file2 = shift(@_);
    my $res = system("diff \"$file1\" \"$file2\" &>/dev/null");
    print("$res is $? for $file1 and $file2\n");
    if ($res >= 2) {
        # if diff returned with an error
        return 0;
    } else {
        return($res);
    }
}

# Tests if the argument at the given index exists 
#   and is not an option (i.e. doesn't begin with '-')
sub is_arg {
    my $k = shift(@_);
    my @arg = split(//,$ARGV[$k]);
    if ($ARGV[$k] && $arg[0] ne "-") {
        return 1;
    } else {
        return 0;
    }
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
                if ($j+1 == scalar(@opts) && is_arg($i+1)) {
                    interactive($ARGV[$i+1]);
                    $i++;
                } else {
                    die("Error: Option 'i' requires additional argument...");
                }
            } elsif ($opts[$j] eq "l") {
                list();
            } elsif ($opts[$j] eq "r") {
                # Run the retrieve function if it is the last option in the group
                #   and the next arg exists
                if ($j+1 == scalar(@opts) && is_arg($i+1)) {
                    retrieve($ARGV[$i+1]);
                    $i++;
                } else {
                    die("Error: Option 'r' requires additional argument...$ARGV[$i+1]");
                }
            }
        }

    } else {
        main($arg);
    }
}
