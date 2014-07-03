<?php

/**
 * @file
 * (sj_lesson_builder_config.admin.inc) Config Form for Swing Jammerz Lesson Builder
 */

/**
 * Implements hook_form
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_lesson_builder_admin_form($form, &$form_state, $id = null) {
  $lesson = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_lesson_builder">' . t('Retour au listing des cours') .'</a>'
  );
  
  if ($id) {
    $lesson = db_select('sj_lessons', 'l')
            ->fields('l')
            ->condition('sjl_id', $id, '=')
            ->execute()
            ->fetch();
    
    $submit = t('Modifier');
  }
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->name : '',
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['type'] = array(
       '#type' => 'select',
       '#title' => t('Type de cours'),
       '#options' => array(
          'lindy hop'       => t('Lindy Hop'),
          'charleston solo' => t('Charleston Solo')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->type : ''
   );
  
  $form['day'] = array(
       '#type' => 'select',
       '#title' => t('Jour du cours'),
       '#options'    => array(
         'lundi'    => t('Lundi'),
         'mardi'   => t('Mardi'),
         'mercredi' => t('Mercredi'),
         'jeudi'  => t('Jeudi'),
         'vendredi'    => t('Vendredi'),
         'samedi'  => t('Samedi'),
         'dimanche'    => t('Dimanche')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->day : ''
   );

  $form['time'] = array(
    '#type' => 'textfield',
    '#title' => t('Heure du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->time : '',
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['level'] = array(
       '#type' => 'select',
       '#title' => t('Niveau du cours'),
       '#options' => array(
         'débutant'      => t('Débutant'),
         'intermédiaire' => t('Intermédiaire'),
         'avancé'        => t('Avancé')
       ),
       '#default_value' => $lesson instanceof stdClass ? $lesson->level : ''
   );
  
  $form['place'] = array(
    '#type' => 'textfield',
    '#title' => t('Lieu du cours'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->place : '',
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );
  
  $form['max_capacity_leader'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de place maximum cavalier'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->max_capacity_leader : '',
    '#size' => 50,
    '#maxlength' => 3,
    '#required' => true
  );
  
  $form['max_capacity_follower'] = array(
    '#type' => 'textfield',
    '#title' => t('Nombre de place maximum cavalière'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->max_capacity_follower : '',
    '#size' => 50,
    '#maxlength' => 3,
    '#required' => true
  );
  
  if ($id) {
    $form['capacity_leader'] = array(
      '#type' => 'textfield',
      '#title' => t('Nombre de place restantes cavalier'),
      '#default_value' => $lesson->capacity_leader,
      '#size' => 50,
      '#maxlength' => 3,
      '#required' => true
    );

    $form['capacity_follower'] = array(
      '#type' => 'textfield',
      '#title' => t('Nombre de place restantes cavalière'),
      '#default_value' => $lesson->capacity_follower,
      '#size' => 50,
      '#maxlength' => 3,
      '#required' => true
    );
  }
  
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Actif'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->enabled : 1
  );
  
  $form['full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Plein'),
    '#default_value' => $lesson instanceof stdClass ? $lesson->full : 0
  );
  
  $form['year'] = array(
      '#type' => 'textfield',
      '#title' => t('Année correspondant au cours'),
      '#default_value' => $lesson instanceof stdClass ? $lesson->year : '2014',
      '#size' => 50,
      '#maxlength' => 128,
      '#required' => true
    );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => isset($submit) ? $submit : t('Créer'),
      '#submit' => array('sj_lesson_builder_admin_submit'),
  );
 
  $form['submit']['#validate'][] = 'sj_lesson_builder_admin_validate';
  $form_state['l_id'] = $id;
  
  return $form;
}

/**
 * Implements hook_validate()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_lesson_builder_admin_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['max_capacity_leader'])) {
    form_set_error('max_capacity_leader', t('Vous devez indiquer le nombre de place maximum pour les cavaliers'));
  }
  
  if (!is_numeric($form_state['values']['max_capacity_follower'])) {
    form_set_error('max_capacity_follower', t('Vous devez indiquer le nombre de place maximum pour les cavalières'));
  }
}

/**
 * Implements hook_submit()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_lesson_builder_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  if (!$form_state['l_id']) {
    $query = db_insert('sj_lessons');
    
    $capacity_leader   = $values['max_capacity_leader'];
    $capacity_follower = $values['max_capacity_follower'];
    
    drupal_set_message(t('Cours intitulé <b>@name</b> créé', array('@name' => $values['name'])));
  } else {
    $query = db_update('sj_lessons')
            ->condition('sjl_id', $form_state['l_id'], '=');
    
    $capacity_leader   = $values['capacity_leader'];
    $capacity_follower = $values['capacity_follower'];
    
    drupal_set_message(t('Cours intitulé <b>@name</b> a été mis à jour', array('@name' => $values['name'])));
  }
  $query->fields(array(
          'name' => $values['name'],
          'type' => $values['type'],
          'day' => $values['day'],
          'time' => $values['time'],
          'level' => $values['level'],
          'place' => $values['place'],
          'max_capacity_leader' => $values['max_capacity_leader'],
          'max_capacity_follower' => $values['max_capacity_follower'],
          'capacity_leader' => $capacity_leader,
          'capacity_follower' => $capacity_follower,
          'enabled' => $values['enabled'],
          'full' => $values['full'],
          'year' => $values['year']
      ))
      ->execute();
  
  $form_state['redirect'] = 'admin/config/sj_lesson_builder';
}

/**
 * Delete a lesson
 *
 * @param int $id 
 */
function sj_lesson_builder_admin_delete($id) {
  $lesson = db_select('sj_lessons', 'l')
          ->fields('l', array('name'))
          ->condition('sjl_id', $id)
          ->execute()
          ->fetch();
  
  if (!$lesson) {
    drupal_set_message(t("Cours non trouvé"));
    
    drupal_goto('/admin/config/sj_lesson_builder');
  }
  
  
  db_delete('sj_lessons')
        ->condition('sjl_id', $id)
        ->execute();
  
  drupal_set_message(t("Le cours intitulé <b>" . $lesson->name . "</b> a été supprimé"));
  
  drupal_goto('/admin/config/sj_lesson_builder');
}
