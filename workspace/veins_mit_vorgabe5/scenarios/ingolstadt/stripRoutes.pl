#!/bin/perl

my $file = "ingolstadt.rou.xml";

open FILE, $file;


my $counter = 0;
print "<routes>";
while (<FILE>) {

	if ($_ =~ /route (edges.*)$/) {
		print "<route id=\"route$counter\" $1\n";
		$counter++;
	}
}
print "</routes>\n";

close FILE;
