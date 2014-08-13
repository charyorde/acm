<?php
function course_list(){
	$content = '<div class="block" >'.drupal_get_form('acm_course_search_form').'</div>';
	$content .= '<div style="clear:both" ></div>';
	$header = array(
		array('data' => t('Id'), 'field' => 'id', 'sort' => 'asc'),
		array('data' => t('Student'),'field' => 'uid', 'sort' => 'asc'),
		array('data' => t('Grade'),'field' => 'grade', ),
		array('data' => t('Total score'),'field' => 'totalscore', ),
		array('data' => t('Submitted by'),'field' => 'submittedby', ),	
		array('data' => t('View')),
		array('data' => t('Update')),
	);
	$id = $_GET['ono'];
	if(!empty($_GET['ono'])){
		$Sql="SELECT c.id,c.uid,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c where c.id =".$id;
	}
	else{
	
	$Sql="SELECT c.id,c.uid,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c " ;
	}
	$count = "SELECT count(*) FROM acm_course";	
	
	$query = pager_query($Sql,5,0,$count);
	while($row = db_fetch_object($query)){
	   $user=user_load($row->uid);
	   $stud=$user->name;
	   $data[] = array( $row->id, $stud,$row->grade,$row->totalscore,$row->submittedby, l('View', 'student/course/'.$row->id.'/view'),l('Edit','student/course/update/',array('query'=>array('acmID'=>$row->id))) );
	}
	$content .= theme('table', $header, $data);
	$content .= theme('pager', 5);
	return $content;
}

function acm_course_search_form($form_id){
	
	$form['#method'] = 'get';
	$form['#token'] = FALSE;
	$form['#form_build_id'] = FALSE;
	$form['#form_id'] = FALSE;
	$form['ono'] = array(
		'#type' => 'textfield',
		'#title' => t('View order number'),
		'#attributes' => array( 'maxlength' => '128', 'size'=> '30'),
		'#prefix' => '<div class="form-inline views-exposed-form"> <div class="views-exposed-widget">',
		'#suffix' => '</div>',
		'#default_value' => isset($_GET['ono'])?$_GET['ono']:'',
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#attributes' => array( 'name' => ''),
		'#prefix' => '<div class="views-exposed-widget">',
		'#suffix' => '</div></div>',
		'#value' => 'Apply',
	 );  
	
	return $form;
}

function acm_course_update(){
	return drupal_get_form('acm_course_update_form');
	}
function acm_course_update_form($form_id){
	$acm_id = $_GET['acmID'];
		
	$query = db_query("SELECT c.id,c.exam_score,c.test_score,u.name,u.uid,ctc.title,ctc.nid,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c,node_revisions ctc, users u WHERE c.course=ctc.nid AND c.uid=u.uid AND c.id=".$acm_id);
	 $row = db_fetch_object($query);
	 
	 $student_lists=get_user_list('student');
	$student_options = array();
	$student_options[$row->uid] = $row->name;
	foreach($student_lists as $student_list){
		$student_options[$student_list->uid] = $student_list->name;
	}
	$form['uid'] = array(
		'#title' => t('Student'),
		'#type' => 'select',
		'#options' => $student_options,
		'#required' => TRUE,
		'#default_value' =>$row->name ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>' ,     
	);
	$course_lists = get_course_list('course_content');
	$course_options = array();
	$course_options[$row->nid] = $row->title; 
	foreach($course_lists as $course_list){
		$course_options[$course_list->nid] = $course_list->title;
	}
	$form['course'] = array(
		'#title' => t('Course'),
		'#type' => 'select',
		'#options' => $course_options,
		'#required' => TRUE,
		'#default_value' =>$row->title ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>' ,     
	);
	 $form['exam_score'] = array(
		'#title' => t('Exam Score'),
		'#type' => 'textfield', 
		'#default_value' =>$row->exam_score,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['test_score'] = array(
		'#title' => t('Test Score'),
		'#type' => 'textfield',
		'#default_value' =>$row->test_score ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>' ,     
	);
	$form['matriculationnumber'] = array(
		'#title' => t('Matriculation number'),
		'#type' => 'textfield',
		'#default_value' =>$row->matriculationnumber ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['currentgpa'] = array(
		'#title' => t('Current GPA'),
		'#type' => 'textfield',
		'#default_value' =>$row->currentgpa ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['totalscore'] = array(
		'#title' => t('Total Score'),
		'#type' => 'textfield',
		'#default_value' =>$row->totalscore ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['grade'] = array(
		'#title' => t('Grade'),
		'#type' => 'textfield',
		'#default_value' =>$row->grade ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['gradepoint'] = array(
		'#title' => t('Grade Point'),
		'#type' => 'textfield',
		'#default_value' =>$row->gradepoint ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['dropped'] = array(
		'#title' => t('Dropped'),
		'#type' => 'checkbox',
		'#default_value' =>$row->dropped ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['creditload'] = array(
		'#title' => t('Credit Load'),
		'#type' => 'textfield',
		'#default_value' =>$row->creditload ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['approved'] = array(
		'#title' => t('Approved'),
		'#type' => 'checkbox',
		'#default_value' =>$row->approved ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	
	$form['submitted'] = array(
		'#title' => t('Submitted for approval'),
		'#type' => 'checkbox',
		'#default_value' =>$row->submitted ,
		'#prefix' => '<div class="require-data">',
		'#suffix' => '</div>',     
	);
	$form['submit'] = array(
		'#value' => 'Update',
		'#type' => 'submit',
		'#submit' => array('acm_course_update_form_submit'),
		'#prefix' => '<div class="member_submit" >',
		'#suffix' => '</div>',
	);
	 
	 return $form;
	}
function acm_course_update_form_submit($form, &$form_state){
	$values = $form_state['values'];
	
	$update="uid='$values[uid]',course='$values[course]',exam_score='$values[exam_score]',test_score='$values[test_score]',matriculationnumber='$values[matriculationnumber]',currentgpa='$values[currentgpa]',totalscore='$values[totalscore]',grade='$values[grade]',gradepoint='$values[gradepoint]',dropped='$values[dropped]',creditload='$values[creditload]',approved='$values[approved]',submitted='$values[submitted]'";
	$acm_id = $_GET['acmID'];
	$res=update_sql("UPDATE {acm_course} SET $update WHERE id =".$acm_id);
	if($res){
	drupal_goto('student/course/list');
	}
}

function viewsdata($id){
	$output ="<div></div>" ;	
	$output .="<div class='title'><h3>Course Details</h3></div>" ;	
	$output .= "<table class='course_details' cellpadding='4' width='100%'>" ;
		
	$query = db_query("SELECT c.id,c.exam_score,c.test_score,u.name,c.matriculationnumber,c.currentgpa,c.totalscore,c.grade,c.gradepoint,c.dropped,c.creditload,c.approved,c.submitted,c.submittedby FROM acm_course c,content_type_course_content ctc, users u WHERE c.course=ctc.nid AND c.uid=u.uid AND c.id=".$id);
	$row = db_fetch_object($query);

	if($row->name){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Student Name:</td><td>".$row->name."</td></tr>";
	}
	if($row->exam_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Exam Score:</td><td>".$row->exam_score."</td></tr>";
	}
	if($row->test_score){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Test Score:</td><td>".$row->test_score."</td></tr>";
	}
	if($row->title){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Course:</td><td>".$row->title."</td></tr>";
	}
	if($row->matriculationnumber){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Matriculation Number:</td><td>".$row->matriculationnumber."</td></tr>";
	}
	if($row->currentgpa){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Current GPA:</td><td>".$row->currentgpa."</td></tr>";
	}
	if($row->totalscore){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Total Score:</td><td>".$row->totalscore."</td></tr>";
	}
	if($row->grade){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Grade:</td><td>".$row->grade."</td></tr>";
	}
	if($row->gradepoint){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Grade Point:</td><td>".$row->gradepoint."</td></tr>";
	}
	if($row->dropped){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Dropped:</td><td>".$row->dropped."</td></tr>";
	}
	if($row->creditload){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Credit Load:</td><td>".$row->creditload."</td></tr>";
	}
	if($row->approved){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Approved:</td><td>".$row->approved."</td></tr>";
	}
	if($row->submitted){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Submitted:</td><td>".$row->submitted."</td></tr>";
	}
	if($row->submittedby){
		$output.="<tr><td colspan='3'style='font-weight:bold;'>Submitted By:</td><td>".$row->submittedby."</td></tr>";
	}
	$output.= '</table>';
	
 return $output;
}
