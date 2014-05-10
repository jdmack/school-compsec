#!/usr/bin/perl

my %addresses = ();

# Collect addresses from alloc
for(my $i = 0; $i < 100; $i++) {

    my $address = `alloc`;
    chomp($address);

    if(exists $address{$address}) {
        $addresses{$address}++;
    }
    else {
        $addresses{$address} = 1;
    }
}

my %subaddresses_2 = sub_address(\%addresses, 2);
print_address_hash(%subaddresses_2);

my %subaddresses_3 = sub_address(\%addresses, 3);
print_address_hash(%subaddresses_3);

################################################################################
#   sub_address
################################################################################
sub sub_address
{
    my %addresses = %{$_[0]};
    my $digits = $_[1];
    print "digits: $digits\n";
    #print "# of addresses sent to sub_address: " . hash_size(%addresses) . "\n";

    my %subaddresses = ();

    my $tailing_zeroes = "";
    for(my $i = 0; $i < (8 - $digits); $i++) {
        $trailing_zeroes .= "0";
    }

    foreach my $address (keys %addresses) {

        my $subaddress = substr($address, 2, $digits);
        $subaddress = "0x" . $subaddress . $trailing_zeroes;

        if(exists $subaddresses{$subaddress}) {
            $subaddresses{$subaddress}++;
        }
        else {
            $subaddresses{$subaddress} = 1;
        }

        # print "address: $address";
        # print "\tsubaddress: $subaddress\n";
    }

    return %subaddresses;
}

################################################################################
#   print_hash_size
################################################################################
sub hash_size
{
    my (%params) = @_;
    my @keys = keys %params;
    my $size = @keys;
    return $size;

}

################################################################################
#   print_address_hash
################################################################################
sub print_address_hash
{
    my (%addresses) = @_;

    print "\n# of addresses: " . hash_size(%addresses) . "\n";

    foreach my $address (sort { $addresses{$b} <=> $addresses{$a} } keys %addresses) {
        print "$address: $addresses{$address}\n";
    }
}

