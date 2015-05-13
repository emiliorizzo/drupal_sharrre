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
 $vals = _sharrre_get_settings();
  foreach($services as $service => $set){
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
    '#default_value' => _sharrre_get_sett($vals,'sharrre',$service,false),
    '#description' => t("Enable @service icon",$targs),
    );
    
    $form[$service][$service.'_title'] = array(
    '#type' => 'textfield',
    '#size' => 20, 
    '#maxlength' => 64, 
    '#title' => t('Title'),
    '#default_value' => _sharrre_get_sett($vals,$service,'title', $set['title']),
    '#description' => t("Text on @service icon",$targs),
    );
  }
   foreach($settings as $prop => $desc){
    if( $prop != 'title' ){
     $form[$service][$service.'_'.$prop] = array(
                       '#type' => 'checkbox',
                       '#title' => $prop,
                       '#default_value' => _sharrre_get_sett($vals,$service,$prop,FALSE),
                       '#description' => t($desc['desc']),
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
 $settings = array_merge($settings, array_keys($services));
 $varr = array();
  foreach( $services as $service => $set){
   foreach( $settings as $prop){
    if( isset( $form_state['values'][$service.'_'.$prop] ) ){
      $val = $form_state['values'][$service.'_'.$prop];
      if( ( $prop == 'title' ) && ( empty( $val ) ) ){
       $val = $set['title']; 
      }
     $varr[$service][$prop] = $val;
     unset( $form_state['values'][$service.'_'.$prop] );
     unset($val);
    }
   }
  }
 $form_state['values']['sharrre_settings'] = serialize($varr);
}
 
 