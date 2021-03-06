<style>
	.main_content{
		width: 84% !important;
	}
</style>

<script type="text/javascript">


	function mostrarIndice(id2){
	    $("#indice_data" + id2).modal(); 
	}
    
[% IF socio_data.usr_nro_socio %]	
    function showModalReporteCatalogo(id2){
        $("#modal_reporte_catalogo" + id2).modal('show'); 
    }

    function enviarReporteCatalogo(id2){

        hideReservar(id2);
        objAH               = new AjaxHelper(updateEnviarReporteCatalogo);
        objAH.debug         = true;
        objAH.showOverlay   = true;
        //para busquedas combinables
        objAH.url           = URL_PREFIX+'/opac-reporte-catalogo.pl';
        objAH.id2           = id2;
        objAH.informe       = $("#text_reporte_catalogo" + id2).val();
        objAH.sendToServer();
        $("#modal_reporte_catalogo" + id2).modal('hide'); 
        
            
    }

    function updateEnviarReporteCatalogo(responseText){
        var Messages = JSONstring.toObject(responseText);
        setMessages(Messages);
        
        infoReservas();
        infoSanciones();
    }

[% END %]	

	function ProcessGBSBookInfo(booksInfo) {
		for (id in booksInfo) {
		 var element = document.getElementById(id);
		 var bookInfo = booksInfo[id];
		 if (bookInfo) {
		  element.href = bookInfo.preview_url;
		  element.style.display = '';
		 }
	   }
	 }

	function detalleMARC(id3){
		objAH               = new AjaxHelper(updateInfoMARC);
		objAH.debug         = true;
	    objAH.showOverlay   = true;
		objAH.url			= URL_PREFIX+"/opac-MARCDetail.pl";
		objAH.id3           = id3;
		//se envia la consulta
		objAH.sendToServer();
	}

	function updateInfoMARC(responseText){
		        $('#detalleMARC').html(responseText);
				$('#detalleMARC').modal();
	}
		 

    $(document).ready(function() {
    	$('.fancylink').fancybox();
    	$('.nano').nanoScroller();
    });
</script>

<section class="detalle_registro" id="detalle_registro_[% id1 %]">  
          <h1>[% nivel1_obj.getTituloStringEscaped %]  </h1>
          <h3>[% nivel1_obj.getAutorStringEscaped %] </h3> 
</section>

[% IF estadoDeColeccion %]
    <div class="detalle_completo_niveles">
        <div class="main-subcontent" >
            <div class="subcontent-unit-border" >
                <div class="round-border-topleft"></div>
                    <div class="main-subcontent">
						 <legend class="trigger trigger_estado_coleccion_[% id1 %] click" >
						 <h3>[% "Estado de Colecci&oacute;n" | i18n %]  <i class="icon-arrow-down" style="float:right"></i> </h3>

						 </legend>
						         <div id="estado_coleccion[% id1 %]" class="detalle_total estado_coleccion[% id1 %]">
									<ul class="listado_sin_margen estado_coleccion unstyled">
										[% FOREACH anio IN estadoDeColeccion.keys.sort %]
			                            [% IF estadoDeColeccion.$anio.keys %]
			                            <li>
			                                [% IF  (estadoDeColeccion.$anio.size > 1 || (estadoDeColeccion.$anio.keys.first && estadoDeColeccion.$anio.keys.first != '#'))||
			                                (estadoDeColeccion.$anio.item('#').size > 1 || (estadoDeColeccion.$anio.item('#').keys.first && estadoDeColeccion.$anio.item('#').keys.first != '#')) 
			                                       %]
			                                   [% IF anio != '#' %] <b>[% anio %]</b>  [% END %]

			                                  [% FOREACH volumen IN estadoDeColeccion.$anio.keys.sort %]
			                                    
			                                      [% IF  estadoDeColeccion.$anio.$volumen.keys.size > 1 || estadoDeColeccion.$anio.$volumen.keys.sort.first != '#' %]
			                                       [% IF volumen != '#' %] <b>[% volumen %]</b>[% END %]
			                                        (
			                                          [% FOREACH fasciculo IN estadoDeColeccion.$anio.$volumen.keys.sort %]

																 [% PERL %]
																	print C4::AR::Filtros::link_to( text =>     "[% fasciculo %]",
																									url=>"[% url_prefix %]/opac-detail.pl", 
																									params =>   ["id1=[% id1 %]","id2=[% estadoDeColeccion.$anio.$volumen.$fasciculo %]"],
																									title =>    "[% 'Mostrar Detalle del Registro' | i18n %]",
																									class => 	"link_to_detail"
																								) ;
																 [% END %]
			                                                
			                                          [% END %]
			                                         )
			                                      [% ELSE %]
			                                        [% PERL %]
			                                          print C4::AR::Filtros::link_to( text =>     "[% volumen %]",
			                                                        url=>"[% url_prefix %]/opac-detail.pl", 
			                                                        params =>   ["id1=[% id1 %]","id2=[% estadoDeColeccion.$anio.$volumen.item('#') %]"],
			                                                        title =>    "[% 'Mostrar Detalle del Registro' | i18n %]",
			                                                        class =>  "link_to_detail"
			                                                      ) ;
			                                        [% END %]
			                                      [% END %]

			                                  [% END %]

			                                [% ELSE %]
			                                    [% PERL %]
			                                      print C4::AR::Filtros::link_to( text =>     "[% anio %]",
			                                                    url=>"[% url_prefix %]/opac-detail.pl", 
			                                                    params =>   ["id1=[% id1 %]","id2=[% estadoDeColeccion.$anio.item('#').item('#') %]"],
			                                                    title =>    "[% 'Mostrar Detalle del Registro' | i18n %]",
			                                                    class =>  "link_to_detail"
			                                                  ) ;
			                                    [% END %]
			                                [% END %]
			                            </li>
			                            [% END %]
			                            [% END %]

									</ul>
									[% IF issn %]
										<div class="right">
											<div class="google-books">
												<a id="ISSN:[% issn %]"  style="display:none" target="_blank">
													<img src="/includes/css/gbs_preview_button1.gif" border="0" style="margin: 0"/>
												</a>
											</div>
											<script src="//books.google.com/books?jscmd=viewapi&bibkeys=ISSN:[% issn %]&callback=ProcessGBSBookInfo"></script>
										</div>
									[% END %]
							   </div>
							   
					</div>
			</div>
		</div>
	</div>
	<script type="text/javascript">makeToggle('estado_coleccion[% id1 %]','trigger_estado_coleccion_[% id1 %]',null,true);</script>
[% END %]

[% INCLUDE 'opac-detail_partial_N2_reducido.inc' %]
<div id="resultadoReserva"></div>
