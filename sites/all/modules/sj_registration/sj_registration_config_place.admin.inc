<?php

/**
 * @file
 * (sj_registration_config_place.admin.inc) Place Config Form for Swing Jammerz Registration Module
 */

/**
 * Place creation / edition hook_form()
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_registration_place_admin_form($form, &$form_state, $id = null) {
  $place = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_registration">' . t('Retour à la page de configuration') .'</a>'
  );
  
  if ($id) {
    $place = db_select('sj_places', 'p')
            ->fields('p')
            ->condition('id', $id)
            ->execute()
            ->fetch();
    
    $submit = t('Modifier');
  }
  
  $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom du lieu'),
      '#default_value' => $place instanceof stdClass ? $place->name : null,
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
  );
  
  $form['address'] = array(
      '#type' => 'textfield',
      '#title' => t('Adresse du lieu'),
      '#default_value' => $place instanceof stdClass ? $place->address : null,
      '#size' => 50,
      '#maxlength' => 128
  );
  
  $form['postcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Code postal:'),
    '#default_value' => $place instanceof stdClass ? $place->postcode : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('Ville:'),
    '#default_value' => $place instanceof stdClass ? $place->city : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['latitude'] = array(
       '#type' => 'textfield',
       '#title' => t('Latitude du lieu'),
       '#default_value' => $place instanceof stdClass ? $place->latitude : null,
       '#size' => 50,
       '#maxlength' => 128,
       '#required' => true
   );
  
  $form['longitude'] = array(
       '#type' => 'textfield',
       '#title' => t('Longitude du lieu'),
       '#default_value' => $place instanceof stdClass ? $place->longitude : null,
       '#size' => 50,
       '#maxlength' => 128,
       '#required' => true
   );
  
  $form['year'] = array(
      '#type' => 'textfield',
      '#title' => t('Année correspondant au lieu'),
      '#default_value' => $place instanceof stdClass ? $place->year : null,
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
    );
  
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Actif'),
    '#default_value' => $place instanceof stdClass ? $place->enabled : 1
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($submit) ? $submit : t('Créer'),
      '#submit' => array('sj_registration_place_admin_submit'),
  );
  
  $form_state['id'] = $id;
  
  return $form;
}

/**
 * Implements hook_submit()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_registration_place_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  $fields = array(
          'name' => $values['name'],
          'address' => $values['address'],
          'postcode' => $values['postcode'],
          'city' => $values['city'],
          'latitude' => $values['latitude'],
          'longitude' => $values['longitude'],
          'year' => $values['year'],
          'enabled' => $values['enabled']
  );
  
  if (!$form_state['id']) {
    $query = db_insert('sj_places');
    
    $fields['created_at'] = format_date(time(), 'custom', 'Y-m-d H:i:s');
    
    drupal_set_message(t('Lieu intitulé <b>@name</b> créé', array('@name' => $values['name'])));
  } else {
    $query = db_update('sj_places')
            ->condition('id', $form_state['id'], '=');
    
    drupal_set_message(t('Lieu intitulé <b>@name</b> a été mis à jour', array('@name' => $values['name'])));
  }
  
  $query->fields($fields)
      ->execute();
  
  $form_state['redirect'] = 'admin/config/sj_registration';
}

/**
 * Delete a lieu
 *
 * @param int $id 
 */
function sj_registration_place_admin_delete($id) {
  $place = db_select('sj_places', 'p')
          ->fields('p', array('name'))
          ->condition('id', $id)
          ->execute()
          ->fetch();
  
  if (!$place) {
    drupal_set_message(t("Lieu non trouvé"));
    
    drupal_goto('/admin/config/sj_registration');
  }
  
  
  db_delete('sj_places')
        ->condition('id', $id)
        ->execute();
  
  drupal_set_message(t("Le lieu intitulé <b>" . $place->name . "</b> a été supprimé"));
  
  drupal_goto('/admin/config/sj_registration');
}