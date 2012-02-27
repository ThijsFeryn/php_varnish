--TEST--
Check for varnish authentication
--SKIPIF--
<?php if (!extension_loaded("varnish") || !file_exists('tests/config.php')) print "skip"; ?>
--FILE--
<?php 

include 'tests/config.php';

/* XXX test exceptions */

foreach ($args_all as $args) {
	$va = new VarnishAdmin($args);
	$va->connect();
	var_export($va->auth());
	echo "\n";
}

?>
--EXPECT--
true
true
true
true
