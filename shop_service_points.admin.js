function shop_service_point_edit_form(spid=null,type) {
  var req='/admin/service_point/edit';
  jQuery.post(req, { service_point:spid,type:type}, function(data) {
    var result = jQuery.parseJSON(data);
    jQuery.fancybox({
      content: result,
      width:350,
      height:550,
      fitToView : false,
      autoSize : false


    });
  });
  return false;

}


function shop_service_point_delete(spid=null,type) {
  if (confirm("Точно удалить?")) {
    var req='/admin/service_point/delete';
    jQuery.post(req, { service_point:spid,type:type}, function(data) {
      window.location.reload();
    });
  } else {
    return false;
  }
}
