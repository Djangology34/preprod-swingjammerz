function initialize() {
  var map;
  var bounds = new google.maps.LatLngBounds();
  var mapOptions = {
      mapTypeId: 'roadmap',
      scrollwheel: false
  };

  // Display a map on the page
  map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
  map.setTilt(45);

  // Multiple Markers
  var markers = JSON.parse(Drupal.settings.sj_gmaps.locations);

  // Display multiple markers on a map
  var gmarkers = [];
  var infoWindow = new google.maps.InfoWindow(), marker, i;

  // Loop through our array of markers & place each one on the map  
  for( i = 0; i < markers.length; i++ ) {
      var position = new google.maps.LatLng(markers[i][2], markers[i][3]);
      bounds.extend(position);
      marker = new google.maps.Marker({
          position: position,
          map: map,
          title: markers[i][0]
      });

      gmarkers.push(marker);
      
      // Allow each marker to have an info window    
      google.maps.event.addListener(marker, 'click', (function(marker, i) {
          return function() {
              infoWindow.setContent('<div class="info-content"><b>' + markers[i][0] + '</b><br/>' + markers[i][1] + '</div>');
              infoWindow.open(map, marker);
          }
      })(marker, i));

      // Automatically center the map fitting all markers on the screen
      map.fitBounds(bounds);

      //This function fires when a user clicks a link.
      jQuery('.open-marker').click(function(e) {
        e.preventDefault();
        
        //Get the data key variable from the link
        var key = jQuery(this).data('key');

        //Call the trigger event for the map market from the gmarkers array 
        google.maps.event.trigger(gmarkers[key],'click');
      });
  }

  // Override our map zoom level once our fitBounds function runs (Make sure it only runs once)
  var boundsListener = google.maps.event.addListener((map), 'bounds_changed', function(event) {
      //this.setZoom(10);
      google.maps.event.removeListener(boundsListener);
  });
}