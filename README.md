# Drupal Sharrre Social Icons

 Implements Sharrre Social Media Plugin

 Sharrre, a plugin for sharing buttons : Facebook, Twitter, Google Plus, Digg, Delicious
 by: Julien Hany - http://hany.fr/
 http://sharrre.com/

## Instalation

- Install Libraries API module,http://drupal.org/project/libraries
- Download Sharrre 1.3.5 from https://github.com/Julienh/Sharrre/archive/1.3.5.zip
- Copy Sharrre plugin files in sites/all/libraries/sharrre
- Install and enable soscial_sharrre module
- Goto -> admin/config/social_sharrre, and configure module
- Put   <?php print render($social_sharrre_icons);?> in node-tpl files.

## Configuration Options

### Sharre Template

  You can select predefined templates.

### Manual

 You can select which icons to use and options for each.

### In theme folder

 - Fully customizable option.
 - The files reside on your theme folder.
 - See examples/README.md




