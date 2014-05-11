#! /usr/bin/perl -w

my $samplesCount = 100000;
my $testCount = 5000;
my $i;

print("1\n$samplesCount\n");

for ($i = 0; $i < $samplesCount; $i++) {
	print(int(rand(1 << 31)) , " ");
}

print "\n$testCount\n";
for ($i = 0; $i < $testCount; $i++) {
	my ($a, $b) = (int(rand(1 << 31)), int(rand(1 << 31)));

	print(($a < $b ? $a : $b) , " " , ($a > $b ? $a : $b) , "\n");
}
