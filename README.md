Drupal Sharrre Social Icons

INTRODUCTION
------------

The Drupal 7 Social Sharrre module implements Sharrre Social Media Plugin,
by Julien Hany.

 * Sharrre, a plugin for sharing buttons : Facebook, Twitter, Google Plus, Digg, Delicious
   by: Julien Hany - http://hany.fr/
  http://sharrre.com/

REQUIREMENTS
------------

This module requires the following modules:

 * Libraries API (https://www.drupal.org/project/libraries)
 * Sharrre 1.3.5 (https://github.com/Julienh/Sharrre/archive/1.3.5.zip)

INSTALLATION
------------

* Install Libraries API module, http://drupal.org/project/libraries

* Download Sharrre 1.3.5 from https://github.com/Julienh/Sharrre/archive/1.3.5.zip

* Copy Sharrre plugin files in sites/all/libraries/sharrre

* Install social_sharrre module, as you would normally install a contributed Drupal module.
  See: https://drupal.org/documentation/install/modules-themes/modules-7
  for further information.


CONFIGURATION
-------------

* Goto -> admin/config/social_sharrre, and configure module

* Put   <?php print render($social_sharrre_icons);?> in node-tpl files.


CONFIGURATION OPTIONS
---------------------
  The module has three configuration modes:

  - Sharre Template

      You can select predefined templates.

  - Manual

      You can select which icons to use and options for each.

 -  In theme folder

    Fully customizable option.
    The files reside in your theme folder.
    See examples/README.md




