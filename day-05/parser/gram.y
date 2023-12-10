%define api.pure true
%parse-param { struct Almanac** a }

%{

#include "map.h"

%}

%union {
  int i;

  struct Almanac* alm;
  struct List* list;
}

%token SEEDS SEED_SOIL SOIL_FERTILIZER FERTILIZER_WATER WATER_LIGHT LIGHT_TEMP TEMP_HUMIDITY HUMIDITY_LOCATION

%token <i> NUMBER


%type <alm> almanac
%type <list> seeds seed_soil_list soil_fert_list fert_water_list water_light_list light_temp_list temp_hum_list hum_loc_list

%start almanac

%%

almanac:  seeds
          seed_soil_list
          soil_fert_list
          fert_water_list
          water_light_list
          light_temp_list
          temp_hum_list
          hum_loc_list   {
            Almanac* alm = new_almanac();
            
          }
  ;

seeds: NUMBER {

    }
  | seeds NUMBER {

    }
  ;

seed_soil_list: seed_soil {

    }
  | seed_soil_list seed_soil {

    }
  ;

seed_soil: NUMBER NUMBER NUMBER {

    }
  ;


%%