bool slagbomen_zijn_open = false;

void open_brug(){
//    while(1){
//        input();
//        if(is_er_verkeer()){
//            break;
//        }
//
//        if(is_wind_veilig()){
//            return;
//        }
//    }
//    _delay_ms(1000);

    slagbomen_dicht();
    CONTROLEPANEELSLAGBOOMDICHTLEDAAN;

    _delay_ms(1000);

    h_bridge_set_percentage(50);
    _delay_ms(1000);
    h_bridge_set_percentage(0);
    CONTROLEPANEELOPENLEDAAN;
    DoorvaartToegestaanLeds();

    _delay_ms(1000);

    while(1){
        if(KNOPOPENINGEDRUKT){
            brug_dicht();
            break;
        }
    }
}

void brug_dicht(){
    DoorvaartVerbodenLeds();
    h_bridge_set_percentage(-30);
    while(1){
        if(BRUGDICHTLIMITINGEDRUKT){
            h_bridge_set_percentage(0);
            CONTROLEPANEELOPENLEDUIT;

            _delay_ms(1000);

            slagbomen_open();

            CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
            break;
        }
    }
}

void slagbomen_dicht(){
    servo1_set_percentage(100);
    servo2_set_percentage(100);
    slagbomen_zijn_open = false;
    CONTROLEPANEELSLAGBOOMDICHTLEDAAN;
}

void slagbomen_open(){
    servo1_set_percentage(-100);
    servo2_set_percentage(-100);
    slagbomen_zijn_open = true;
    CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
}

void leds(){
    if(is_er_verkeer()){
        CONTROLEPANEELVOETGANGERSLEDAAN;
    } else {
        CONTROLEPANEELVOETGANGERSLEDUIT;
    }

    if(is_er_een_boot()){
        CONTROLEPANEELBOTENLEDAAN;
    } else {
        CONTROLEPANEELBOTENLEDUIT;
    }

    if(is_wind_veilig()){
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDAAN;
    } else {
        CONTROLEPANEELWEERSOMSTANDIGHEDENLEDUIT;
    }

    if(schakelaar_modus){
        CONTROLEPANEELAUTOMATISCHLEDAAN;
    } else {
        CONTROLEPANEELAUTOMATISCHLEDUIT;
    }

    if(slagbomen_zijn_open){
        CONTROLEPANEELSLAGBOOMDICHTLEDUIT;
    } else {
        CONTROLEPANEELSLAGBOOMDICHTLEDAAN;
    }

}

void knoppen(){
    if(KNOPOPENINGEDRUKT){
        open_brug();
    }

   if(KNOPSLAGBOMENINGEDRUKT){
        if(slagbomen_zijn_open){
            slagbomen_dicht();
        } else {
            slagbomen_open();
        }
        _delay_ms(500);
    }
}

void lineair(){
    slagbomen_open();
    DoorvaartVerbodenLeds();
    while(1){
        input();
        leds();
        knoppen();
    }
}
