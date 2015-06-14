# Examples

## In theme Folder example

- Copy 'sharrre-style' folder to your theme folder
- Go to -> admin/config/social_sharre -> Configuration Type -> Select: 'In theme Folder' 
- Save Configuration
 
### Name
 
you can change 'sharrre-style' with the name you want.

- Go to -> admin/config/social_sharre
- -> In Theme Folder Configuration -> Custom Style Name: (ex) 'my-style-name'
 
 - Rename:
  
 -- [ your_theme_path ] / sharre-style   to ->   [ your_theme_path ] / my-style-name
 
 - In [ your_theme_path ] / my-style-name :
   
   -- Rename : sharre-style.css  -> my-style-name.css
   -- Rename : sharre-style.css -> my-style-name.js

### html template
see http://sharrre.com/#documentation
 
 By default social_sharrre write a div container, filled with sharrre default template.
 The cointainer ID is 'sharrre-html-template', 
 and is removed by js files after reading the content.

Two ways to customize:

- write directly on js file
- set in your theme node_preprocess function

#### Write directly on js file

( '.sharrre-icons' ).each(function(i, obj){
          $( this ).sharrre({

#### Set in your theme node_preprocess function

- Implement theme_node_preprocess function
- set  $variables['social_sharrre_icons']['html_template']['html']['#markup'] = [your_html_code];

Example:
in your theme template.php:

```
function [your_theme_name]_preprocess_node($variables){
 $variables['social_sharrre_icons']['html_template']['html']['#markup'] = '<div class="box"><div class="left">Share</div><div class="middle"><a href="#" class="facebook">f</a><a href="#" class="twitter">t</a><a href="#" class="googleplus">+1</a></div><div class="right">{total}</div></div>';
}
```

