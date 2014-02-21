#!/usr/bin/perl

use strict;

my $cmd_line = join(" ", @ARGV[1..@ARGV]," ");
#print $cmd_line,"\n";

open COMMAND, ">cmd.gnu";


print COMMAND "set term png; set output '$ARGV[0]'; set grid; set yrange [0:21]; $cmd_line";
close COMMAND;

`/usr/bin/gnuplot cmd.gnu`;

unlink "cmd.gnu";
