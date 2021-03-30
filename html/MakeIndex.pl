#!/usr/bin/perl

use strict;
use warnings;

# -----------------------------------------------------------------
# Index building perl script for DX web pages.
#
# The following perl modules must be installed to use:
#      HTML-Index, HTML-Tagset, HTML-Parser, HTML-Tree
#
# To run this to build a new index, issue the following command in
# the root html directory:
#       perl MakeIndex.pl `find . -name "*.htm"` > srchidx.js
#
# The resultant file is a giant javascript string list consisting of
# page-name|page-title|(keyword number-of-occurances,)*.
#
# -----------------------------------------------------------------
use HTML::TreeBuilder;

my $MINSTRLEN = 4;
my $TITLESTRVAL = 500;

my @commonList = <DATA>;
chomp @commonList;

print "profiles = new Array(\n";

my $i = 0;
my @files = @ARGV;

foreach my $fileName (@files) {
    $fileName =~ s/^\.\///;
    my %uniqueWords;
    my $tree = HTML::TreeBuilder->new();
    $tree->parse_file($fileName);
    my $title = $tree->find_by_tag_name('title');
    my @titlestr = $title->content_list();
    $titlestr[0] =~ s/,/ /g;
    my @text = $tree->as_text();
    foreach my $sym (@text) {
    
        # turn all non-text based characters to space
	$sym =~ s/[^a-zA-Z0-9\-_]/ /g;
	
	$sym =~ s/--/ /g; # turn hiphen into space

	# Now create an array with all words >= $MINSTRLEN letters 
	# in length and uniquify them.
	
	my @symar = split(" ", $sym);
	foreach my $sym2 (@symar) {
	    if(length($sym2) >= $MINSTRLEN) {
		$sym2 = lc($sym2);
		# don't add too common words from data past __END__
		my $test = 1;
		foreach my $cw (@commonList) {
		    if($sym2 eq $cw) {
			$test = 0;
			last;
		    }
		}
		if($test) {
		    $uniqueWords{$sym2}++;
		}
	    }
	}
	
	# Now add the Title's key words, they get $TITLESTRVAL
	# times the value as the words in the text.
	
	@symar = split(" ", $titlestr[0]);
	foreach my $sym2 (@symar) {
	    if(length($sym2) >= $MINSTRLEN) {
		$sym2 = lc($sym2);
		# don't add too common words from data past __END__
		my $test = 1;
		foreach my $cw (@commonList) {
		    if($sym2 eq $cw) {
			$test = 0;
			last;
		    }
		}
		if($test) {
		    $uniqueWords{$sym2} += $TITLESTRVAL;
		}
	    }
	}	
    }
    print "\t\"" . $fileName . "|";
    print $titlestr[0] . "|";
    my @sortwords = sort { $uniqueWords{$b} <=> $uniqueWords{$a} } keys %uniqueWords;
    foreach my $word (@sortwords) {
	print " $word $uniqueWords{$word}";
    }
    print "\"";
    if($i != $#files) {
	print ",\n";
    }
    $tree->delete;
    $i++;
}

print "\n);\n";

__END__
about
after
also
been
both
contents
customer
does
each
either
from
have
here
hereof
home
however
into
legal
like
make
many
most
next
only
same
shall
should
since
some
such
sure
table
that
their
then
thereof
these
this
those
used
user
using
value
well
were
when
will
with
within
without
your
deal
item
whose
what
onto
html
know
thus
over
than
away
they
whether
much
thing
another
more
itself
even
want
would
upon



