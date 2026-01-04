#!/usr/bin/env perl

# $Id: prime.convert.pl,v 1.2 2026/01/04 06:18:22 scott Exp scott $

use strict;
use warnings;
use POSIX qw(floor);
use Scalar::Util qw(looks_like_number);

sub prime {
    my ($min_val, $max_val) = @_;
    my $num_primes = 0;

    return $num_primes if $max_val < 2;

    $num_primes++ if $min_val < 3;

    for my $i (3 .. $max_val) {
        next if $i % 2 == 0;

        my $is_prime = 1;
        my $limit = floor(sqrt($i));

        for (my $up = 3; $up <= $limit; $up += 2) {
            if ($i % $up == 0) {
                $is_prime = 0;
                last;
            }
        }

        $num_primes++ if $is_prime;
    }

    return $num_primes;
}

sub main {
    my @argv = @_;
    my $min_val = 1;
    my $max_val = 50000000;

    if (@argv == 2) {
        $min_val = $argv[0];
        $max_val = $argv[1];
    } elsif (@argv == 1) {
        $max_val = $argv[0];
    }

    if ($min_val > $max_val) {
        print STDERR "ERROR: min $min_val must be <= max $max_val\n";
        return 1;
    }

    my $num_primes = prime($min_val, $max_val);

    print "min = $min_val, max = $max_val, num_primes = $num_primes\n";
    return 0;
}

exit main(@ARGV);
