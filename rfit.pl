#!/usr/bin/perl

srand;

my @list =  (	"{46,363}",
	"{70,474}",
	"{93,587}",
	"{117,671}",
	"{140,743}",
	"{164,821}",
	"{187,884}",
	"{210,923}");

my @rlist;

while (@list) 
{
        push(@rlist, splice(@list, rand @list, 1));
}

foreach $item (@rlist)
{
	print "$item,\n";
}
