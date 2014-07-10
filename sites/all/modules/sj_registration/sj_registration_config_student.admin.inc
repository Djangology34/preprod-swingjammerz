<?php

/**
 * @file
 * (sj_registration_config_student.admin.inc) Student Config Form for Swing Jammerz Registration Module
 */

/**
 * Student edition hook_form()
 *
 * @param array $form
 * @param array $form_state
 * @param int   $id
 *
 * @return array 
 */
function sj_registration_student_admin_form($form, &$form_state, $id) {
  $student = null;
  $form['link'] = array(
    '#markup' => '<a href="\admin\config\sj_registration">' . t('Retour à la page de configuration') .'</a>'
  );
  
  $student = db_select('sj_students', 's')
          ->fields('s')
          ->condition('sjs_id', $id)
          ->execute()
          ->fetch();
  
  $form['firstname'] = array(
    '#type' => 'textfield',
    '#title' => t('Prénom:'),
    '#default_value' => $student instanceof stdClass ? $student->firstname : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );

  $form['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom:'),
    '#default_value' => $student instanceof stdClass ? $student->lastname : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true
  );

  $form['gender'] = array(
    '#type' => 'radios',
    '#title' => t("Votre genre:"),
    '#default_value' => $student instanceof stdClass ? $student->gender : null,
    '#options' => array(
        'masculin' => t('Masculin'),
        'féminin' => t('Féminin')
    ),
    '#required' => TRUE
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Adresse email:'),
    '#default_value' => $student instanceof stdClass ? $student->email : null,
    '#size' => 50,
    '#maxlength' => 128,
    '#required' => true,
    '#element_validate' => array('myelement_email_validate')
  );

  $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Numéro de téléphone:'),
    '#default_value' => $student instanceof stdClass ? $student->phone : null,
    '#size' => 50,
    '#maxlength' => 128
  );

  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Adresse:'),
    '#default_value' => $student instanceof stdClass ? $student->address : null,
    '#size' => 50,
    '#maxlength' => 255
  );

  $form['postcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Code postal:'),
    '#default_value' => $student instanceof stdClass ? $student->postcode : null,
    '#size' => 50,
    '#maxlength' => 128
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('Ville:'),
    '#default_value' => $student instanceof stdClass ? $student->city : null,
    '#size' => 50,
    '#maxlength' => 128
  );
  
  $countries = country_get_list();
      
  $form['country'] = array(
      '#type' => 'select',
      '#title' => t('Pays:'),
      '#options' => $countries,
      '#default_value' => $student instanceof stdClass ? $student->country : null,
  );

  // Pass
  $passes = db_select('sj_passes', 'p')
          ->fields('p', array('sjp_id', 'name', 'nb_lessons'))
          ->execute()
          ->fetchAll();

  if (!$passes && !count($passes)) {
    drupal_set_message(t('<div class="alert alert-dismissable alert-warning">Aucun pass trouvé...</div>'));
  }

  $options = array();
  foreach ($passes as $pass) {
    $options[$pass->sjp_id] = $pass->name;
  }

  $form['pass_id'] = array(
    '#type' => 'radios',
    '#title' => t("Pass choisi:"),
    '#default_value' => $student instanceof stdClass ? $student->pass_id : null,
    '#options' => $options,
    '#required' => TRUE
  );
  
  // Lessons
  $lessons = db_select('sj_lessons', 'l')
        ->fields('l', array('sjl_id', 'name'))
        ->execute()
        ->fetchAll();

  $options = array();
  foreach ($lessons as $lesson) {
    $options[$lesson->sjl_id] = $lesson->name;
  }

  $nb_lessons = $pass->nb_lessons;
  if ($nb_lessons === 'all') {
    $nb_lessons = 'tous les';
  }
  
  $query = db_select('sj_lessons', 'l');
  $query->leftJoin('sj_students_lessons', 'sl', 'l.sjl_id = sl.sj_lesson_id');
          
  $lessons_selected = $query->fields('l', array('sjl_id', 'level'))
          ->condition('sl.sj_student_id', $student->sjs_id)
          ->execute()
          ->fetchAll();
  
  $selection = array();
  foreach($lessons_selected as $value) {
    $selection[] = $value->sjl_id;
  }
  
  $form_state['selection'] = $selection;
  
  if (count($lessons_selected)) {
    $form['level'] = array(
        '#markup' => '<br/><b>' . t('Niveau de l\'élève:') . '</b> ' . $lessons_selected[0]->level . '<br/>'
    );
  }
  
  $form['lessons'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Peut s\'inscrire à @nb_lessons cours:', array('@nb_lessons' => $nb_lessons)),
        '#default_value' => count($selection) ? $selection : null,
        '#options' => $options
      );

  $form['payment_method'] = array(
      '#type' => 'radios',
      '#title' => t("Méthode de paiement:"),
      '#default_value' => $student instanceof stdClass ? $student->payment_method : null,
      '#options' => array(
          'paypal' => 'Paypal',
          'cheque' => 'Chèque'
      ),
      '#required' => TRUE
  );
  
  $form['payed'] = array(
    '#type' => 'checkbox',
    '#title' => t('A payé'),
    '#default_value' => $student instanceof stdClass ? $student->payed : 1,
  );
  
  $form['waiting_list'] = array(
    '#type' => 'checkbox',
    '#title' => t('Est sur liste d\'attente'),
    '#default_value' => $student instanceof stdClass ? $student->waiting_list : 0,
  );
  
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Actif'),
    '#default_value' => $student instanceof stdClass ? $student->enabled : 1,
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Modifier'),
      '#submit' => array('sj_registration_student_admin_submit'),
  );
  
  $form_state['id'] = $id;
  
  return $form;
}

/**
 * Student form Implements hook_submit()
 *
 * @param type $form
 * @param type $form_state 
 */
function sj_registration_student_admin_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  $fields = array(
      'firstname' => $values['firstname'],
      'lastname' => $values['lastname'],
      'gender' => $values['gender'],
      'email' => $values['email'],
      'phone' => $values['phone'],
      'address' => $values['address'],
      'postcode' => $values['postcode'],
      'city' => $values['city'],
      'country' => $values['country'],
      'pass_id' => $values['pass_id'],
      'payed' => $values['payed'],
      'payment_method' => $values['payment_method'],
      'waiting_list' => $values['waiting_list'],
      'enabled' => $values['enabled']
  );
  
  $query = db_update('sj_students')
          ->condition('sjs_id', $form_state['id'], '=')
          ->fields($fields)
          ->execute();
  
  // Manage lessons
  $lessons = array();
  foreach ($values['lessons'] as $lesson) {
    if ($lesson) {
      $lessons[] = $lesson;
    }
  }
  
  $insert = array_diff($lessons, $form_state['selection']);
  if (count($insert)) {
    foreach($insert as $lesson_id) {
      $query = db_insert('sj_students_lessons')
              ->fields(array(
                  'sj_student_id' => $form_state['id'],
                  'sj_lesson_id'  => $lesson_id
                  ))
              ->execute();
    }     
  }

  $delete = array_diff($form_state['selection'], $lessons);
  if (count($delete)) {
    foreach($delete as $lesson_id) {
      $query = db_delete('sj_students_lessons')
              ->condition('sj_student_id', $form_state['id'])
              ->condition('sj_lesson_id', $lesson_id)
              ->execute();
    }
  }
  
  drupal_set_message(t('Elève nommé <b>@name</b> a été mis à jour', array('@name' => $values['firstname'] . ' ' . $values['lastname'])));
  
  $form_state['redirect'] = 'admin/config/sj_registration';
}

/**
 * Delete a student
 *
 * @param int $id 
 */
function sj_registration_student_admin_delete($id) {
  $student = db_select('sj_students', 's')
          ->fields('s', array('name'))
          ->condition('sjs_id', $id)
          ->execute()
          ->fetch();
  
  if (!$student) {
    drupal_set_message(t("student non trouvé"));
    
    drupal_goto('/admin/config/sj_registration');
  }
  
  
  db_delete('sj_students')
        ->condition('sjs_id', $id)
        ->execute();
  
  drupal_set_message(t("L'élève nommé <b>" . $student->name . "</b> a été supprimé"));
  
  drupal_goto('/admin/config/sj_registration');
}