--TEST--
Check for varnish stop/start
--SKIPIF--
<?php if (!extension_loaded("varnish") || !file_exists('tests/config.php')) print "skip"; ?>
--FILE--
<?php 

include 'tests/config.php';

/* XXX test exceptions */

foreach ($args_all as $args) {
	$args['timeout'] = 2000;
	$va = new VarnishAdmin($args);
	$va->connect();
	$va->auth();

 	echo $va->stop() . "\n";
	sleep(2);
 	echo $va->start() . "\n";
	sleep(2);
}

?>
--EXPECT--
200
200
200
200
200
200
200
200
