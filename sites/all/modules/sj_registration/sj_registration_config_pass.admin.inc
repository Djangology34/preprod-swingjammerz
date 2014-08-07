<?php

/**
 * @file
 * (sj_registration_config_pass.admin.inc) Pass Config Form for Swing Jammerz Registration Module
 */

/**
 * Pass creation / edition hook_form()
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_registration_pass_admin_form($form, &$form_state, $id = null) {
  $pass = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_registration">' . t('Retour à la page de configuration') .'</a>'
  );
  
  if ($id) {
    $pass = db_select('sj_passes', 'p')
            ->fields('p')
            ->condition('sjp_id', $id)
            ->execute()
            ->fetch();
    
    $submit = t('Modifier');
  }
  
  $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom du pass'),
      '#default_value' => $pass instanceof stdClass ? $pass->name : '',
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
  );
  
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description du pass'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->description : null,
    '#required' => false
  );
  
  $form['price'] = array(
       '#type' => 'textfield',
       '#title' => t('Prix du pass'),
       '#default_value' => $pass instanceof stdClass ? $pass->price : '',
       '#size' => 50,
       '#maxlength' => 128,
       '#required' => true,
       '#element_validate' => array('element_validate_number')
   );
  
  $form['currency'] = array(
       '#type' => 'select',
       '#title' => t('Devise'),
       '#options' => array(
         'EUR' => 'EUR'
       ),
       '#default_value' => $pass instanceof stdClass ? $pass->currency : 'EUR'
   );
  
  $form['year'] = array(
      '#type' => 'textfield',
      '#title' => t('Année correspondant au pass'),
      '#default_value' => $pass instanceof stdClass ? $pass->year : null,
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
  );

  $form['nb_lessons'] = array(
      '#type' => 'select',
      '#title' => t('Nombre de lessons permis pour le pass'),
      '#options'    => array(
          'no'  => 'aucun',
          'all' => 'tous'
      ),
      '#default_value' => $pass instanceof stdClass ? $pass->nb_lessons : 1
  );
  
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Actif'),
    '#default_value' => $pass instanceof stdClass ? $pass->enabled : 1
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($submit) ? $submit : t('Créer'),
      '#submit' => array('sj_registration_pass_admin_submit'),
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
function sj_registration_pass_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  $fields = array(
          'name' => $values['name'],
          'description' => $values['description'],
          'price' => $values['price'],
          'currency' => $values['currency'],
          'year' => $values['year'],
          'nb_lessons' => $values['nb_lessons'],
          'enabled' => $values['enabled']
  );
  
  if (!$form_state['id']) {
    $query = db_insert('sj_passes');
    
    $fields['created_at'] = format_date(time(), 'custom', 'Y-m-d H:i:s');
    
    drupal_set_message(t('Pass intitulé <b>@name</b> créé', array('@name' => $values['name'])));
  } else {
    $query = db_update('sj_passes')
            ->condition('sjp_id', $form_state['id'], '=');
    
    drupal_set_message(t('Pass intitulé <b>@name</b> a été mis à jour', array('@name' => $values['name'])));
  }
  
  $query->fields($fields)
      ->execute();
  
  $form_state['redirect'] = 'admin/config/sj_registration';
}

/**
 * Delete a pass
 *
 * @param int $id 
 */
function sj_registration_pass_admin_delete($id) {
  $pass = db_select('sj_passes', 'p')
          ->fields('p', array('name'))
          ->condition('sjp_id', $id)
          ->execute()
          ->fetch();
  
  if (!$pass) {
    drupal_set_message(t("Pass non trouvé"));
    
    drupal_goto('/admin/config/sj_registration');
  }
  
  
  db_delete('sj_passes')
        ->condition('sjp_id', $id)
        ->execute();
  
  drupal_set_message(t("Le pass intitulé <b>" . $pass->name . "</b> a été supprimé"));
  
  drupal_goto('/admin/config/sj_registration');
}