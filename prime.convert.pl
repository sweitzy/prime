#!/usr/bin/env perl

# $Id: prime.convert.pl,v 1.1 2026/01/04 06:06:15 scott Exp scott $

use strict;
use warnings;

sub prime {
    my ($min, $max) = @_;
    my $num_primes = 0;

    # if all negative numbers, nothing to do
    return $num_primes if $max < 2;

    # special case < 3: 2 is prime
    $num_primes++ if $min < 3;

    for my $i (3 .. $max) {
        # special case: even number
        next if $i % 2 == 0;

        my $is_prime = 1;

        for (my $up = 3; $up * $up <= $i; $up += 2) {
            if ($i % $up == 0) {
                $is_prime = 0;
                last;
            }
        }

        $num_primes++ if $is_prime;
    }

    return $num_primes;
}

# main
my ($min, $max) = (-2, 50000000);

if (@ARGV == 2) {
    $min = $ARGV[0];
    $max = $ARGV[1];
} elsif (@ARGV == 1) {
    $max = $ARGV[0];
}

if ($min > $max) {
    die "ERROR: min $min must be <= max $max\n";
}

my $num_primes = prime($min, $max);

print "min = $min, max = $max, num_primes = $num_primes\n";
exit 0;
