<?php
/**
 * @file
 * Admin page callbacks for the meme_share module.
 */

/**
 * Form builder; Configure meme_share module
 *
 * @ingroup forms
 * @see system_settings_form()
 */
 
function sharrre_admin_form($form, &$form_state){
 $services = _sharrre_services(); 
 $settings = _sharrre_settings(); 
 $vals = variable_get('sharrre_settings',NULL);
 if( $vals ){
  $vals = unserialize($vals);
 }

  foreach($services as $service){
   $targs = array('@service' => ucfirst($service));
   $pref = 'sharre_'.$service;
   
   $form[$service] = array(
    '#type' => 'fieldset',
    '#title' => t('@service Settings',$targs),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
     );
     
  if( $service != 'sharrre' ){
    $form[$service]['sharrre_'.$service] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#default_value' => _sharrre_get_sett($vals,'sharrre',$service,FALSE),
    '#description' => t("Enable @service icon",$targs),
    );
    
    $form[$service][$service.'_title'] = array(
    '#type' => 'textfield',
    '#size' => 20, 
    '#maxlength' => 64, 
    '#title' => t('Title'),
    '#default_value' => _sharrre_get_sett($vals,$service,'title',NULL),
    '#description' => t("Text on @service icon",$targs),
    );
  }
   foreach($settings as $prop => $desc){
    if( $prop != 'title' ){
     $form[$service][$service.'_'.$prop] = array(
                       '#type' => 'checkbox',
                       '#title' => $prop,
                       '#default_value' => _sharrre_get_sett($vals,$service,$prop,FALSE),
                       '#description' => t($desc),
                      );
    }
   }
  }
 $form = system_settings_form($form);
 array_unshift($form['#submit'], 'sharrre_admin_form_submit');
 return $form;
 }
 
 /**
 * Admin Form Submit Callback
 * **/

function sharrre_admin_form_submit($form,&$form_state){
 $services = _sharrre_services(); 
 $settings = array_keys(_sharrre_settings()); 
 $settings = array_merge($settings, $services);
 $varr = array();
  foreach( $services as $service ){
   foreach( $settings as $prop){
    if( isset( $form_state['values'][$service.'_'.$prop] ) ){
     $varr[$service][$prop] = $form_state['values'][$service.'_'.$prop];
     unset( $form_state['values'][$service.'_'.$prop] );
    }
   }
  }
 $form_state['values']['sharrre_settings'] = serialize($varr);
}
 
 