<?php
drupal_add_css(drupal_get_path('module', 'shop_service_points') .'/shop_service_points.admin.css');
drupal_add_js(drupal_get_path('module','shop_service_points').'/shop_service_points.admin.js');

function shop_service_points_shops_form(){
  $result_html = '';
  if (isset($_SESSION['result_service']['message_type']) && $_SESSION['result_service']['message_type']!='' &&
    isset($_SESSION['result_service']['message']) && $_SESSION['result_service']['message']!='' ) {
    $result_html ='<div class="result result-'.$_SESSION['result_service']['message_type'].'" >'.$_SESSION['result_service']['message'].'</div>';
    unset ($_SESSION['result_service']);
  }

  $output=$result_html.'
  <div class="download_block">
    <h1>Загрузка магазинов на сайт</h1>
    <form enctype="multipart/form-data" method="post" action="/admin/service_xlsx/upload"  >
      <div class="left_block" >
        <span>Выберите файл для закачки:</span>
        <input type="file" name="service" />
         <input type="hidden" name="type" value="shop" />
      </div>
      <input type="submit" value="Загрузить XLSX с магазинами" class="right_block shop_button" />
      <div class="clear" ></div>
    </form>
    <p>Скачать пример xlsx файла:
    <a href="/'.drupal_get_path('module', 'shop_service_points').'/files/service_example.xlsx" >Скачать</a></p>
  </div>';

  $output.=<<<EOF
<button class='shop_button'  onclick="shop_service_point_edit_form(null,'shop')">Добавить магазин</button>
<button class='shop_button'  onclick="shop_service_point_delete('all','shop')">Удалить все</button>

EOF;

  $services=shop_service_points_get_all();

  $output.=<<<EOF
  <table class="service_points_table">
    <thead>
    <tr>
      <td>Город</td>
      <td>Адрес</td>
      <td>Широта</td>
      <td>Долгота</td>
      <td>Телефон</td>
      <td>Время работы</td>
     </tr>
    </thead>
    <tbody>
EOF;
  $i=1;
  foreach ($services as $service) {
    $even_or_odd=$i%2==0?'even':'odd';
    $output.= <<<EOF
   <tr class="$even_or_odd">
    <td style="font-weight: 600">$service->city
     <br>
     <img title="Редактировать магазин" style="cursor: pointer" onclick="shop_service_point_edit_form($service->spid,'shop')" src="/sites/all/modules/_shop_modules/shop_product/icons/edit.png">
     <img title="Удалить магазин" style="cursor: pointer" src="/sites/all/modules/_shop_modules/shop_product/icons/delete.png" onclick="shop_service_point_delete($service->spid)">
    </td>
    <td>$service->address</td>
    <td>$service->latitude</td>
    <td>$service->longitude</td>
    <td>$service->phone</td>
    <td>$service->worktable</td>
   </tr>
EOF;
    $i++;
  }
  $output.=<<<EOF
  </tbody></table>
EOF;
  return $output;
}
function shop_service_points_form(){
  $result_html = '';
  if (isset($_SESSION['result_service']['message_type']) && $_SESSION['result_service']['message_type']!='' &&
    isset($_SESSION['result_service']['message']) && $_SESSION['result_service']['message']!='' ) {
    $result_html ='<div class="result result-'.$_SESSION['result_service']['message_type'].'" >'.$_SESSION['result_service']['message'].'</div>';
    unset ($_SESSION['result_service']);
  }

  $output=$result_html.'
  <div class="download_block">
    <h1>Загрузка сервис центров на сайт</h1>
    <form enctype="multipart/form-data" method="post" action="/admin/service_xlsx/upload"  >
      <div class="left_block" >
        <span>Выберите файл для закачки:</span>
        <input type="file" name="service" />
        <input type="hidden" name="type" value="service" />
      </div>
      <input type="submit" value="Загрузить XLSX с сервис центрами" class="right_block shop_button" />
      <div class="clear" ></div>
    </form>
    <p>Скачать пример xlsx файла:
    <a href="/'.drupal_get_path('module', 'shop_service_points').'/files/service_example.xlsx" >Скачать</a></p>
  </div>';

  $output.=<<<EOF
<button class='shop_button'  onclick="shop_service_point_edit_form(null,'service')">Добавить центр</button>
<button class='shop_button'  onclick="shop_service_point_delete('all','service')">Удалить все</button>

EOF;

  $services=shop_service_points_get_all('service');

  $output.=<<<EOF
  <table class="service_points_table">
    <thead>
    <tr>
      <td>Город</td>
      <td>Адрес</td>
      <td>Широта</td>
      <td>Долгота</td>
      <td>Телефон</td>
      <td>Время работы</td>
     </tr>
    </thead>
    <tbody>
EOF;
  $i=1;
  foreach ($services as $service) {
    $even_or_odd=$i%2==0?'even':'odd';
    $output.= <<<EOF
   <tr class="$even_or_odd">
    <td style="font-weight: 600">$service->city
     <br>
     <img title="Редактировать центр" style="cursor: pointer" onclick="shop_service_point_edit_form($service->spid,'service')" src="/sites/all/modules/_shop_modules/shop_product/icons/edit.png">
     <img title="Удалить центр" style="cursor: pointer" src="/sites/all/modules/_shop_modules/shop_product/icons/delete.png" onclick="shop_service_point_delete($service->spid)">
    </td>
    <td>$service->address</td>
    <td>$service->latitude</td>
    <td>$service->longitude</td>
    <td>$service->phone</td>
    <td>$service->worktable</td>
   </tr>
EOF;
    $i++;
  }
  $output.=<<<EOF
  </tbody></table>
EOF;
  return $output;
}

function shop_service_points_edit_form(){
  $point='';
  if(!empty($_POST['service_point'])) {
    $spid = htmlspecialchars($_POST['service_point']);
    $point = shop_service_points_get($spid);

  }
  $type=$_POST['type'];
  $output= <<<EOF
        <form method="post" action='/admin/service_point/save' xmlns="http://www.w3.org/1999/html">
        <input type="hidden"  name="service_point[spid]"  value="$point->spid" />
        <label>Город:</label>
        <textarea class="point_text" type="text" required  name="service_point[city]"   placeholder="Например:Москва" >$point->city</textarea>
        <label>Адрес:</label>
        <textarea class="point_text" type="text" required name="service_point[address]"  placeholder="Например:просп. Университетский, 107; ТЦ Акварель" >$point->address</textarea>
        <label>Широта:</label>
        <textarea class="point_text" type="text"  required name="service_point[latitude]"  placeholder="Например:48.636558" >$point->latitude</textarea>
        <label>Долгота:</label>
        <textarea class="point_text" type="text" required name="service_point[longitude]"   placeholder="Например:45.691828" >$point->longitude</textarea>
        <label>Телефон:</label>
        <textarea class="point_text" type="text"  required name="service_point[phone]"   placeholder="Например:79608875838" >$point->phone</textarea>
        <label>Время работы:</label>
        <textarea class="point_text" type="text"  name="service_point[worktable]"
        placeholder="Пн-Вс=10:00-22:00" >$point->worktable</textarea><br>
        <input type="hidden" name="service_point[type]" value="$type">
        <input class="right_block shop_button" value="Сохранить" type="submit">
EOF;
  print_r(json_encode($output));
}

function shop_service_points_upload_xlsx()
{
  $type=$_POST['type'];
  $output_error = "";
  $output_success = "";
  if (!isset($_FILES['service']['tmp_name']))
    $output_error = "<p>Файл не загружен.</p>";
  if (!in_array($_FILES['service']['type'], array("application/vnd.ms-excel", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")))
    $output_error = "<p>Файл неправильного формата.</p>";
  if ($output_error == '') {
    require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'site_common') . '/libs/PHPExcel/Classes/PHPExcel/IOFactory.php';
    $xls = PHPExcel_IOFactory::load($_FILES['service']['tmp_name']);
    $xls->setActiveSheetIndex(0);
    $sheet = $xls->getActiveSheet();

    for ($row_index = 2; $row_index <= $sheet->getHighestRow(); $row_index++) {
      $fields = array();
      $fields['city'] = trim($sheet->getCellByColumnAndRow(0, $row_index)->getValue());
      $fields['address'] = trim($sheet->getCellByColumnAndRow(1, $row_index)->getValue());
      $fields['latitude'] = trim($sheet->getCellByColumnAndRow(2, $row_index)->getValue());
      $fields['longitude'] = trim($sheet->getCellByColumnAndRow(3, $row_index)->getValue());
      $fields['phone'] =  trim($sheet->getCellByColumnAndRow(4, $row_index)->getValue());;
      $fields['worktable'] = trim($sheet->getCellByColumnAndRow(5, $row_index)->getValue());
      $fields['type']=$type;
      if(empty($fields['city']))
        continue;

      $existed = db_query('
      SELECT COUNT(*)
      FROM {service_points} sp
      WHERE sp.city = :city  AND sp.address=:address AND sp.type=:type',
        array(":city"=>$fields['city'],":address"=>$fields['address'],":type"=>$fields['type']))->fetchField();
      if($existed==1)
        db_update('service_points')
          ->fields($fields)
          ->condition('city', $fields['name'],'=')
          ->condition('address', $fields['address'],'=')
          ->execute();
      else
        db_insert('service_points')
          ->fields($fields)
          ->execute();
    }
    $output_success="Файл успешно загружен";
  }
  $result = array();
  if ($output_error!= "") {
    $result['message_type'] = 'warning';
    $result['message'] = $output_error;
  }
  else {
    $result['message_type'] = 'success';
    $result['message'] = $output_success;
  }
  $_SESSION['result_service'] = $result;
  drupal_goto('admin/service_points');
}
