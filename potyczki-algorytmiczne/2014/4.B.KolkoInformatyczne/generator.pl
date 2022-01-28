#! /usr/bin/perl

# my $n = 200000000;
my $n = 2000000;
my $m = 200;

print "$n $m\n";

for (my $i = 1; $i <= $n; $i += 1)
{
	print "$i\n";
}
# for (my $i = 1; $i <= $n; $i += 2)
# {
# 	print "$i\n";
# }
# for (my $i = 2; $i <= $n; $i += 2)
# {
# 	print "$i\n";
# }

for (my $i = 0; $i < $m; $i++)
{
	my $f = int(rand($n)) + 1;
	my $t = int(rand($n)) + 1;
	print "$f $t\n";
}
