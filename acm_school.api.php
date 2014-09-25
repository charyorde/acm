<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional documentation for oxygen as well as to document hooks in the standard Drupal manner.
 */

/**
 * @def_group acm_school_hooks Acadaman school module hooks
 * @{
 * Hooks that all school types can implement
 */

/**
 * A student profile is contained in student application
 */ 
function hook_acm_schoolprofile() {

}

/**
 * This hook renders the view for various student application items.
 *
 * Example of student application profile items are:
 *  - sponsor
 *  - course 
 *  - nextofkin
 *  -
 *
 *  This hook is powered by views module. 
 */
function hook_acm_student_application() {

}

/**
 * This hook represents a label of items that should be configured
 * for student application profile view. 
 * 
 * @see hook_admission_application_info for 
 */ 
function hook_acm_student_application_items() {
  // Example of student application profile items for University school type
  $items = array();
  $items['sponsor'] = array(
    'data' => l('Sponsor Information', 'application/sponsor')
  );
  $items['course'] = array(
    'data' => l('Course Information', 'application/course')
);
  return $items;

}

/*
 * This hook defines the structure of admission application steps that 
 * can be implemented per school type. At the end of every application step,
 * this hook is looked up to determine what application form step is next
 */ 
function hook_admission_application_info() {
  $application_form = array(
    'course' => array(
      'title' => 'course',
      'form_id' => 'uni_school_admission_course_form'
    ),
    'sponsor' => array(
      'title' => 'sponsor',
      'form_id' => 'uni_school_admission_sponsors_form'
    ),
    'nextofkin' => array(
      'title' => 'nextofkin',
      'form_id' => 'uni_school_admission_nextofkin_form'
    ),
    'health' => array(
      'title' => 'health',
      'form_id' => 'uni_school_admission_health_form'
    ),
  );
  return $application_form;

}

/**
 * This hook defines the settings for school admission. 
 */ 
function hook_admission_settings($type) {
  // For example, to define the settings for admission status.
  if($type == 'status') {
    $settings['admission']['admission_status_form'] = drupal_get_form('uni_school_admission_settings_form');
  }
  return $settings;
}

/**
 * This hook describes the structure for setting up all the school 
 * modules or features
 */
function hook_school_settings() {
  // Example of school settings
  $settings['type'] = 'configure';
  
  $settings['configure']['admission'] = array(
    'title' => t('Set admission status'),
    'callback url' => t('admin/settings/school/admission/status')
  );
  $settings['configure']['users'] = array(
    'title' => 'Configure users',
    'callback url' => 'admin/settings/school/users'
  );
  $settings['configure']['fees'] = array(
    'title' => 'Setup Fees',
    'callback url' => 'admin/settings/school/fees'
  );
  $settings['configure']['dorm'] = array(
    'title' => 'Configure dormitory allocation',
    'callback url' => 'admin/settings/school/dormitory'
  );
  $settings['configure']['faculty'] = array(
    'title' => 'Add faculty',
    'callback url' => 'admin/settings/school/faculty/add'
  );
  $settings['configure']['department'] = array(
    'title' => 'Add department',
    'callback url' => 'admin/settings/school/department/add'
  );
  $settings['configure']['grade'] = array(
    'title' => 'Configure grading system',
    'callback url' => 'admin/settings/school/grade/gradingsystem'
  );
  
  $settings['configure']['school_settings'] = drupal_get_form('uni_school_school_settings_form');
  
  return $settings;
}

/**
 * A hook that describes the academic levels of a school
 */ 
function hook_academic_level() {
  // Example academic_level for a university school type.
    return drupal_map_assoc(array(100, 200, 300, 400, 500, 600, 700));
}

/**
 * This hook handles the landing page of admissions
 *
 * @todo This hook needs a clear definition and purpose.
 */
function hook_admission() {
}

/**
 * A hook to display a view of student admissions made into a
 * school. This hook is powered by views module.
 */
function hook_admission_application_list() {
  // For example, to display all admissions to a school type of university.
  $admission_view = views_get_view('uni_admission_view');
  return $admission_view;
}

/**
 * This hook displays all faculty in a school.
 *
 * This hook display is powered by views module.
 */ 
function hook_faculty() {

}

/**
 * This hook displays all departments in a school.
 *
 * This hook display is powered by views module.
 */
function hook_department() {

}

/**
 * This hook displays all grades in a school.
 *
 * This hook display is powered by views module
 */
function hook_grade() {
  // For example, a university school type grade display
  $grade_view = views_get_view('uni_grade_view');
  return $grade_view;
}

/**
 * This hook displays all fees in a school.
 *
 * This hook display is powered by views module
 */
function hook_fees() {

}

/**
 * This hook defines all the faculty settings meant to be
 * configured for a school
 */ 
function hook_faculty_settings($type) {
  // Example faculty settings
  $settings['type'] = 'faculty';
  $settings['faculty']['add'] = array(
    'title' => t('Add'),
    'callback url' => 'admin/settings/school/faculty/add'
  );
  $settings['faculty']['add dept'] = array(
    'title' => 'Add department',
    'callback url' => 'admin/settings/school/department/add'
  );
  $settings['faculty']['view'] = array(
    'title' => 'View faculty',
    'callback url' => 'faculty'
  );
  
  if($type == 'add') {
    $settings['faculty']['add_faculty_form'] = drupal_get_form('uni_school_faculty_form');
  }
  if($type == 'add_dept') {
    $settings['faculty']['add_dept_form'] = drupal_get_form('uni_school_faculty_dept_form');
  }
  
  return $settings;

}

/**
 * This hook defines all the department settings meant to be 
 * configured for a school.
 */ 
function hook_department_settings() {
  // Example department settings
  $settings['type'] = 'department';
  $settings['dept']['add'] = array(
    'title' => t('Add'),
    'callback url' => 'admin/settings/school/department/add'
  );
  // add course to a department
  $settings['dept']['add course'] = array(
    'title' => 'Add Course',
    'callback url' => 'admin/settings/school/department/addcourse'
  );
  $settings['dept']['grade point'] = array(
    'title' => 'Set grade point',
    'callback url' => 'admin/settings/school/grade/dept_gradepoint'
  );
  
  if($type == 'add') {
    $settings['dept']['add_dept_form'] = drupal_get_form('uni_school_faculty_dept_form'); //uni_school_add_dept_form()
  }
  if($type == 'addcourse') {
    $settings['dept']['addcourse_form'] = drupal_get_form('uni_school_addcourse_form');
  }
  
  return $settings;
}

/**
 * This hook defines all the programme settings meant to be
 * configured for a school.
 */ 
function hook_programme_settings() {
  // Example programme settings
  $settings['type'] = 'programme';
  $settings['prog']['add'] = array(
    'title' => t('Add'),
    'callback url' => 'admin/settings/school/programme/add'
  );
  if($type == 'add') {
    $settings['prog']['add_prog_form'] = drupal_get_form('uni_school_programme_form');
  }
  
  return $settings;

}

/**
 * This hook defines all the course settings meant to be
 * configured for a school.
 */ 
function hook_course_settings() {
  $form['#attributes'] = array('class' => 'form-horizontal');
  $form['number_of_cas'] = array(
    '#type' => 'select',
    '#title' => t('Number of CAs'),
    '#options' => array(1,2,3,4),
    '#default_value' => variable_get('number_of_cas', (int)''),
  );
  $form['ca_approval_method'] = array(
    '#type' => 'select',
    '#title' => t('CA approval method'),
    '#options' => array('Approved along with exams'),
    '#default_value' => variable_get('ca_approval_method', ''),
  );
  $form['ca_maximum_mark'] = array(
    '#type' => 'textfield',
    '#title' => t('CA maximum mark'),
    '#default_value' => variable_get('ca_maximum_mark', (int)''),
  );
  $form['exam_maximum_mark'] = array(
    '#type' => 'textfield',
    '#title' => t('Exam maximum mark'),
    '#default_value' => variable_get('exam_maximum_mark', (int)'')
  );
  
  return system_settings_form($form);

}

/**
 * This hook defines all the grade settings meant to be
 * configured for a school.
 */ 
function hook_grade_settings() {
  $settings['type'] = 'grade';
  $settings['grade']['configure'] = array(
    'title' => t('Configure grading system'),
    'callback url' => 'admin/settings/school/grade/gradingsystem'
  );
  // set global grading point
  $settings['grade']['grade point'] = array(
    'title' => 'Set grade point',
    'callback url' => 'admin/settings/school/grade/gradepoint'
  );
  // set grading point for a specific department
  // A staff in medicine department should be able to contact the IT
  // staff (Acadaman authorized user) to set medicine department
  // grade point to 7
  $settings['grade']['department grade point'] = array(
    'title' => 'Set department grade point',
    'callback url' => 'admin/settings/school/grade/dept_gradepoint'
  );
  $settings['grade']['grade a student'] = array(
    'title' => 'Grade a student',
    'callback url' => 'admin/settings/school/grade/add'
  );
  $settings['grade']['score a student'] = array(
    'title' => 'Score a student',
    'callback url' => 'admin/settings/school/score/add'
  );
  if($type == 'gradingsystem') {
    $settings['grade']['gradingsystem_form'] = drupal_get_form('uni_school_gradingsystem_settings_form');
  }
  if($type == 'gradepoint') {
    $settings['grade']['gradepoint_form'] = drupal_get_form('uni_school_gradepoint_settings_form'); 
  }
  if($type == 'dept_gradepoint') {
    $settings['grade']['dept_gradepoint_form'] = drupal_get_form('uni_school_dept_gradepoint_settings_form');
  }
  if($type == 'add') {
    $settings['grade']['grade_form'] = drupal_get_form('uni_school_grade_form');
  }
  
  return $settings;

}

/**
 * This hook defines all the score settings meant to be
 * configured for a school.
 */
function hook_score_settings($type) {
  $settings['type'] = 'score';
  if($type == 'add') {
    $settings['score']['score_form'] = drupal_get_form('uni_school_score_form');
  }
  return $settings;

}

/**
 * This hook describes the built-in fees types supported by
 * Acadaman. 
 */
function hook_fees_type() {
  return array('General', 'Program Specific');
}

/**
 * A group that a particular fee belong to.
 *
 * This hook defines the supported fees catalog or structure
 * of a school.
 *
 * For each fee item, it must belong to at least one catalog.
 */
function hook_fee_catalog_info() {

}

/**
 * @}
 */ 
