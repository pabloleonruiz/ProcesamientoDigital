#include "subwindow.h"

subwindow::subwindow(const QString &fileName, const QString &algoritName)
{
    this->close();
    filename=fileName;
    Img = cv::imread(fileName.toStdString(), -1);
    algoritmo=algoritName;
//Se inicializa la ventana
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    QFileInfo ruta(filename);
    salida = ruta.baseName();
    salida.append("_");
    salida.append(algoritmo);

    //Se crean los componentes de la ventana

        createActions();
        createMenus();
        createToolBars();
        createStatusBar();
        init();

        setWindowFilePath(salida);

}

//Subwindow de una subwindow
subwindow::subwindow(const QString &fileName, const QString &algoritName, const Mat &imagen)
{
    salida=fileName;
    Img = imagen;
    algoritmo=algoritName;
//Se inicializa la ventana
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    salida.append("_");
    salida.append(algoritmo);

    //Se crean los componentes de la ventana

        createActions();
        createMenus();
        createToolBars();
        createStatusBar();
        init();

        setWindowFilePath(salida);
}

void subwindow::init()
{

    //Se inicializan los parámetros de los algoritmos
        datos_Dv = (int *) malloc(3*sizeof(int));
        datos_Dv[0] = 2;
        datos_Dv[1] = 1;
        datos_Dv[2] = 1;
        alfa_Dv = 0;

        datos_Hv = (int *) malloc(3*sizeof(int));
        datos_Hv[0] = 2;
        datos_Hv[1] = 1;
        datos_Hv[2] = 1;
        alfa_Hv = 0;

        datos_Mvd_Am = (int *) malloc(4*sizeof(int));
        datos_Mvd_Am[0] = 3;
        datos_Mvd_Am[1] = 1;
        datos_Mvd_Am[2] = 3;
        datos_Mvd_Am[3] = 3;

        datos_Mvd_Pc = (int *) malloc(4*sizeof(int));
        datos_Mvd_Pc[0] = 3;
        datos_Mvd_Pc[1] = 1;
        datos_Mvd_Pc[2] = 3;
        datos_Mvd_Pc[3] = 3;


        int i1 = 0;
        umbral= 0;
        umbral_mayor=0;
        umbral_menor=0;

        long int tam_plano = Img.cols*Img.rows;

        // Se declara la variable para almacener
        // los datos de la imagen de entrada
        float *datos;

        // Se declara la variable auxiliar para
        // almacener los datos de la imagen realzada
        float *resultados;

        // Se reserva memoria para "datos", que va a almacena
        // los tres planos de la imagen color
        datos = (float *) malloc(3 * Img.cols * Img.rows * sizeof (float));

        // Se reserva memoria para "resultados", que va a almacenar
        // el plano de la imagen de niveles de gris local
        resultados = (float *) malloc(Img.cols * Img.rows * sizeof (float));

        // Se reserva memoria para "result", que va a almacenar
        //el plano de la imagen de niveles de gris global
        result = (float *) malloc(Img.cols * Img.rows * sizeof (float));

        if(algoritmo=="Normalizar")
        {
            dialogo13 = new Dialogo_Normalizar();
            dialogo13->exec();
            close();

            int realzadaVistaMax=dialogo13->resultado();

            extraer_datos_realzada(Img,resultados);

            normalizar(resultados, Img.cols, Img.rows, 0.0, realzadaVistaMax);

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(realzadaVistaMax));

            statusBar()->showMessage("Imagen normalizada    Valor: " + QString::number(realzadaVistaMax));
        }

        if(algoritmo=="Lee-Cok")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            dialogo1 = new Dialogo_Lee_Cok();
            dialogo1->exec();
            close();

            op_LeeCok = dialogo1->resultado();
            // Se llama al detector de bordes de Lee y Cok
            Lee_Cok (datos, result, Img.cols, Img.rows, op_LeeCok);

            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados
            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(op_LeeCok));

            statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado   "+"     Operador: " + QString::number(op_LeeCok));
        }

        if(algoritmo=="Direccional")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            dialogo2 = new Dialogo_Direccional();
            dialogo2->exec();
            op_Direccional = dialogo2->resultado();
            // Se llama al detector de bordes Scharcanski-Venetsanopoulos
            Direccional (datos, result, Img.cols, Img.rows,op_Direccional);
            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados
            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(op_Direccional));

            statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado     "+"     Operador: " + QString::number(op_Direccional));

        }
        if(algoritmo=="Dv")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            nombreDetector = "Dv";
            dialogo3 = new Dialogo_Dv(nombreDetector, datos_Dv, alfa_Dv);
            dialogo3->exec();
            datos_Dv = dialogo3->resultado_datos();
            alfa_Dv = dialogo3->resultado_alfa();
            // Se llama al detector de bordes Dv
            Dv (datos, result, Img.cols, Img.rows, datos_Dv[0], datos_Dv[1], alfa_Dv, datos_Dv[2]);

            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados
            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Ventana: " + QString::number(datos_Dv[0])+"    Filtro: " + QString::number(datos_Dv[1]) +"    Alfa: " + QString::number(alfa_Dv) +"    Distancia: " + QString::number(datos_Dv[2]));

        }
        if(algoritmo=="Dv-Hv")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            nombreDetector = "Dv-Hv";
            dialogo3 = new Dialogo_Dv(nombreDetector, datos_Hv, alfa_Hv);
            dialogo3->exec();
            datos_Hv = dialogo3->resultado_datos();
            alfa_Hv = dialogo3->resultado_alfa();

            Dv_hv (datos, result, Img.cols, Img.rows, datos_Hv[0], datos_Hv[1], alfa_Hv, datos_Hv[2]);


            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados
            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Ventana: " + QString::number(datos_Dv[0])+"    Filtro: " + QString::number(datos_Dv[1]) +"    Alfa: " + QString::number(alfa_Dv) +"    Distancia: " + QString::number(datos_Dv[2]));

        }
        if(algoritmo=="Mvd-AM")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            nombreDetector = "Mvd agregadas mutuas";
            dialogo4 = new Dialogo_Mvd(nombreDetector, datos_Mvd_Am);
            dialogo4->exec();
            datos_Mvd_Am = dialogo4->resultado_datos();

            Mvd_agregadas_mutuas (datos, result, Img.cols, Img.rows, datos_Mvd_Am[0],
                                  datos_Mvd_Am[1], datos_Mvd_Am[2], datos_Mvd_Am[3]);

            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];


            // Se crea una imagen en niveles de gris
            // para mostrar los resultados

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Ventana: " + QString::number(datos_Mvd_Am[0]) +
                    "    Distancia: " + QString::number(datos_Mvd_Am[1]) +
                    "    Mediana: " + QString::number(datos_Mvd_Am[2]) +
                    "    Borde: " + QString::number(datos_Mvd_Am[3]));
        }
        if(algoritmo=="Mvd-PC")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            nombreDetector = "Mvd punto central";
            dialogo4 = new Dialogo_Mvd(nombreDetector, datos_Mvd_Pc);
            dialogo4->exec();
            datos_Mvd_Pc = dialogo4->resultado_datos();
            Mvd_punto_central (datos, result, Img.cols, Img.rows, datos_Mvd_Pc[0],
                               datos_Mvd_Pc[1], datos_Mvd_Pc[2], datos_Mvd_Pc[3]);
            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Ventana: " + QString::number(datos_Mvd_Pc[0]) +
                           "    Distancia: " + QString::number(datos_Mvd_Pc[1]) +
                           "    Mediana: " + QString::number(datos_Mvd_Pc[2]) +
                           "    Borde: " + QString::number(datos_Mvd_Pc[3]));

        }
        if(algoritmo=="Shiozaki")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            Shiozaki (datos, result, Img.cols, Img.rows);

            // Se copia "result" en "resultados"
            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];

            // Se crea una imagen en niveles de gris
            // para mostrar los resultados

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado");

        }
        if(algoritmo=="Pietikainen")
        {
            // Se extraen los datos de la imagen original y
            // se copian separados por planos BGR
            // Los datos obtenidos son de tipo float
            extraer_datos_imagen_BGR_separados(Img, datos);

            Pietikainen (datos, result, Img.cols, Img.rows);

            normalizar(result, Img.cols, Img.rows, 0.0,256.0);


            // Se copia "result" en "resultados"

            for(i1 = 0; i1 < tam_plano; i1++)
                resultados[i1]=result[i1];


            // Se crea una imagen en niveles de gris
            // para mostrar los resultados


            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado");
        }
        if(algoritmo=="Manual")
        {
            extraer_datos_realzada(Img, result);

            dialogo5 = new Dialogo_Umbr_Manual();
            dialogo5->exec();
            umbral = dialogo5->resultado();



            // Se llama a la función para umbralizar manualmente
            Manual (result, resultados, Img.cols, Img.rows, umbral);


          // Se crea una imagen en niveles de gris
          // para mostrar los resultados

          crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

          activategray();

          statusBar()->showMessage("Umbral:  " + QString::number(umbral));


        }
        if(algoritmo=="Porcentual")
        {
            extraer_datos_realzada(Img, result);

            dialogo6 = new Dialogo_Umbr_Porcentual();
            dialogo6->exec();
            porcentaje = dialogo6->resultado();


          // Se llama a la función para umbralizar porcentualmente
          Porcentual (result, resultados, Img.cols, Img.rows, porcentaje);


          // Se crea una imagen en niveles de gris
          // para mostrar los resultados

          crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

          activategray();

          statusBar()->showMessage(" Procentaje:  " + QString::number(porcentaje));
        }
        if(algoritmo=="Histeresis")
        {
            extraer_datos_realzada(Img, result);

            dialogo7 = new Dialogo_Histeresis();
            dialogo7->exec();
            umbral_mayor = dialogo7->resultado_mayor();
            umbral_menor = dialogo7->resultado_menor();

            extraer_datos_realzada(Img, result);

            Histeresis (result, resultados, Img.cols, Img.rows, umbral_mayor, umbral_menor);

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(umbral_mayor));
            salida.append("-");
            salida.append(QString::number(umbral_menor));
            statusBar()->showMessage("Umbral superior: " + QString::number(umbral_mayor) +
                                     "     Umbral inferior: " + QString::number(umbral_menor));
        }
        if(algoritmo=="Otsu")
        {
            extraer_datos_realzada(Img, result);
            umbral = Otsu (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, umbral);

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(umbral));
            statusBar()->showMessage(" Umbral:  " + QString::number(umbral));


        }
        if(algoritmo=="Rosin")
        {
            extraer_datos_realzada(Img, result);

            umbral = Rosin (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(umbral*255.0/100.0));


            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(round(umbral*255.0/100.0)));
            statusBar()->showMessage(" Umbral:  " + QString::number(round(umbral*255.0/100.0)));


        }
        if(algoritmo=="Rosin-Normalizado")
        {
            extraer_datos_realzada(Img, result);

            umbral = Rosin_normalizado (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(umbral*255.0));


            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(umbral*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(umbral));


        }
        if(algoritmo=="Rosin-Normalizado_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            umbral = Rosin_normalizado_Acumulado_Inverso (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(umbral*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(umbral*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(umbral));


        }
        if(algoritmo=="Proximidad")
        {
            extraer_datos_realzada(Img, result);
            result_prox = (float *) malloc(2*sizeof(float));
            result_prox = Proximidad (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_prox[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_prox[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_prox[0]));
            umbral=result_prox[0];
        }
        if(algoritmo=="Proximidad_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            result_prox = (float *) malloc(2*sizeof(float));
            result_prox = Proximidad_Acumulado_Inverso (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_prox[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_prox[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_prox[0]));
            umbral=result_prox[0];
        }
        if(algoritmo=="Distancia")
        {
            extraer_datos_realzada(Img, result);

            result_dist = Distante (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_dist*255.0));


            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_dist*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_dist));

            umbral=result_dist;
        }
        if(algoritmo=="Distancia_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            result_dist = Distante_Acumulado_Inverso (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_dist*255.0));


            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_dist*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_dist));
            umbral=result_dist;
        }
        if(algoritmo=="Diagonal")
        {
            extraer_datos_realzada(Img, result);

            result_diag = Diagonal (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_diag*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_diag*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_diag));

            umbral=result_diag;

        }
        if(algoritmo=="Diagonal_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            result_diag = Diagonal_Acumulado_Inverso  (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_diag*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_diag*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_diag));
            umbral=result_diag;

        }
        if(algoritmo=="Adaptativo")
        {
            extraer_datos_realzada(Img, result);

            result_adap = (float *) malloc(2*sizeof(float));
            result_adap = Adaptativo (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_adap[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_adap[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_adap[0]));
            umbral=result_adap[0];
        }
        if(algoritmo=="Adaptativo_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            result_adap = (float *) malloc(2*sizeof(float));
            result_adap = Adaptativo_Acumulado_Inverso (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_adap[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_adap[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_adap[0]));
            umbral=result_adap[0];


        }
        if(algoritmo=="Semi-adaptativo")
        {
            extraer_datos_realzada(Img, result);

            result_semi = (float *) malloc(3*sizeof(float));
            result_semi = Semi_adaptativo (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_semi[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_semi[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_semi[0]));
            umbral=result_semi[0];


        }
        if(algoritmo=="Semi-adaptativo_Acumulado_Inverso")
        {
            extraer_datos_realzada(Img, result);

            result_semi = (float *) malloc(3*sizeof(float));
            result_semi = Semi_adaptativo_Acumulado_Inverso  (result, Img.cols, Img.rows);
            Manual (result, resultados, Img.cols, Img.rows, round(result_semi[0]*255.0));

            crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

            activategray();

            salida.append(QString::number(result_semi[0]*100.0));
            statusBar()->showMessage(" Umbral:  " + QString::number(result_semi[0]));
            umbral=result_semi[0];

        }


        if(algoritmo=="gray_Level")
        {
            bool recortar;
            dialogo9 = new Dialogo_Linear( );
            dialogo9->exec();
            end = dialogo9->resultado_mayor();
            start = dialogo9->resultado_menor();
            inicial= dialogo9->resultado_inicial();
            slope = dialogo9->resultado_pendiente();
            recortar = dialogo9->resultado_recortar();
                if(Img.channels()>=3)
                {

                linear(Img,datos,Img.cols,Img.rows,start,end,inicial,slope,recortar);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());

                activateColor();
                }

                else
                {
                linear(Img,resultados,Img.cols,Img.rows,start,end,inicial,slope,recortar);

                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

                activategray();
                }

                statusBar()->showMessage("Inicio: " + QString::number(start) +
                                     "  Final: " + QString::number(end)+"   Valor Inicial: " + QString::number(inicial)+ "  Slope: " + QString::number(slope));

        }
        if(algoritmo=="Histogram_Slide")
        {
            int desplazamiento=0;

            dialogo10 = new Dialogo_Slide();
            dialogo10->exec();
            desplazamiento = dialogo10->resultado();
                if(Img.channels()>=3)
                {

                hist_slide(Img, datos, desplazamiento);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());

                activateColor();
                }

                else
                {
                hist_slide(Img, resultados, desplazamiento);

                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

                activategray();
                }

                salida.append(QString::number(desplazamiento));

                statusBar()->showMessage("Slide: " + QString::number(desplazamiento));

        }

        if(algoritmo=="Histogram_Shrink")
        {
            dialogo11 = new Dialogo_Shrink();
            dialogo11->exec();
            umbral_mayor = dialogo11->resultado_mayor();
            umbral_menor = dialogo11->resultado_menor();

                if(Img.channels()>=3)
                {

                hist_shrink(Img, datos,umbral_mayor,umbral_menor);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());


                activateColor();
                }

                else
                {

                hist_shrink(Img, resultados,umbral_mayor,umbral_menor);


                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);


                activategray();
                }

                salida.append(QString::number(umbral_mayor));
                salida.append("-");
                salida.append(QString::number(umbral_menor));
                statusBar()->showMessage("Limite superior: " + QString::number(umbral_mayor) +
                                         "     Limite inferior: " + QString::number(umbral_menor));

        }

        if(algoritmo=="Histogram_Stretch")
        {
            dialogo12 = new Dialogo_Stretch();
            dialogo12->exec();
            umbral_mayor = dialogo12->resultado_mayor();
            umbral_menor = dialogo12->resultado_menor();
            float clip_menor = dialogo12->resultado_bajo();
            float clip_mayor = dialogo12->resultado_alto();


                if(Img.channels()>=3)
                {

                hist_stretch(Img, umbral_menor,umbral_mayor,clip_menor,clip_mayor,datos);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());


                activateColor();
                }

                else
                {

                hist_stretch_gray(Img, umbral_menor,umbral_mayor,clip_menor,clip_mayor,resultados);


                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);


                activategray();
                }

                salida.append(QString::number(umbral_mayor));
                salida.append("-");
                salida.append(QString::number(umbral_menor));
                statusBar()->showMessage("Limite superior: " + QString::number(umbral_mayor) +
                                         "     Limite inferior: " + QString::number(umbral_menor)+
                                         "     Porcentaje inferior para recortar" + QString::number(clip_menor)+
                                         "     Porcentaje superior para recortar" + QString::number(clip_mayor));

        }
        if(algoritmo=="Adaptive_Contrast")
        {
            dialogo14 = new Dialogo_Adaptative();
            dialogo14->exec();
            float k1 = dialogo14->resultado_k1();
            float k2 = dialogo14->resultado_k2();
            float size = dialogo14->resultado_size();
            float min = dialogo14->resultado_min();
            float max = dialogo14->resultado_max();


                if(Img.channels()>=3)
                {

                adaptive_contrast_filter(Img,k1,k2,size,min,max,datos);
                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());


                activateColor();
                }

                else
                {

                adaptive_contrast_filter_gray(Img,k1,k2,size,min,max,resultados);
                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);


                activategray();
                }


                statusBar()->showMessage("k1: " + QString::number(k1) +
                                         "     k2: " + QString::number(k2)+
                                         "     Tamaño:" + QString::number(size)+
                                         "     Minimo:" + QString::number(min)+
                                         "     Maximo:" + QString::number(max));

        }
        if(algoritmo=="ColorMap")
        {
            dialogo15 = new Dialogo_ColorMap();
            dialogo15->exec();
            int resultado = dialogo15->resultado();


            applyColorMap(Img,resultadoImg,resultado);
            activateColor();

            salida.append(QString::number(umbral_mayor));

            statusBar()->showMessage("Colormap: " + QString::number(resultado));

        }
        if(algoritmo=="Highpass_Filtering")
        {

                if(Img.channels()>=3)
                {

                resultadoImg=high_pass(Img);

                activateColor();
                }

                else
                {

                resultadoImg=high_pass(Img);

                activategray();
                }

                statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado");


        }
        if(algoritmo=="High_Frequency_Emphasis")
        {
            dialogo16 = new Dialogo_High();
            dialogo16->exec();
            int size = dialogo16->resultado_size();
            bool dc = dialogo16->resultado_dc();
            int cutoff=dialogo16->resultado_cutoff();
            float alfa=dialogo16->resultado_alfa();
            int order=dialogo16->resultado_order();


                if(Img.channels()>=3)
                {

                resultadoImg=High_Freq_Emphasis(Img,size,dc,cutoff,alfa,order);

                activateColor();
                }

                else
                {

                resultadoImg=High_Freq_Emphasis_gray(Img,size,dc,cutoff,alfa,order);

                activategray();
                }


                statusBar()->showMessage("Tamaño del bloque: " + QString::number(size) +
                                         "     Cutoff: " + QString::number(cutoff)+
                                         "     Alfa" + QString::number(alfa)+
                                         "     Orden de filtrado" + QString::number(order));
        }

        if(algoritmo=="Moravec_Filter")
        {
            dialogo17 = new Dialogo_Moravec();
            dialogo17->exec();
            float umbral = dialogo17->resultado();


                if(Img.channels()>=3)
                {

                resultadoImg=moravec_corner_filter(Img,5);

                activateColor();
                }

                else
                {

                resultadoImg=moravec_corner_filter_gray(Img,umbral);

                activategray();
                }

                salida.append(QString::number(umbral));
                statusBar()->showMessage("Umbral: " + QString::number(umbral));

        }

        if(algoritmo=="Homomorphic_Filtering")
        {
            dialogo20 = new Dialogo_Homomorphic();
            dialogo20->exec();
            float upper = dialogo20->resultado_upper();
            float lower = dialogo20->resultado_lower();
            int cutoff=dialogo20->resultado_cutoff();


                if(Img.channels()>=3)
                {

                resultadoImg=homomorphic_filter(Img,upper,lower,cutoff);

                activateColor();
                }

                else
                {

                resultadoImg=homomorphic_filter(Img,upper,lower,cutoff);

                activategray();
                }


                statusBar()->showMessage("Higher Frequency Gain: " + QString::number(upper) +
                                         "     Lower Frequency Gain: " + QString::number(lower)+
                                         "     Cutoff: " + QString::number(cutoff));

        }

        if(algoritmo=="Unsharp_Masking")
        {
            dialogo21 = new Dialogo_Unsharp();
            dialogo21->exec();
            int lower= dialogo21->resultado_mayor();
            int upper = dialogo21->resultado_menor();
            float clip_menor = dialogo21->resultado_bajo();
            float clip_mayor = dialogo21->resultado_alto();


                if(Img.channels()>=3)
                {

                unsharp_filter(Img,lower,upper,clip_menor,clip_mayor,datos);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());

                activateColor();
                }

                else
                {

                unsharp_filter(Img,lower,upper,clip_menor,clip_mayor,resultados);

                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

                activategray();
                }

                statusBar()->showMessage("Limite superior shrink: " + QString::number(umbral_mayor) +
                                         "     Limite inferior shrink: " + QString::number(umbral_menor)+
                                         "     Porcentaje inferior para recortar" + QString::number(clip_menor)+
                                         "     Porcentaje superior para recortar" + QString::number(clip_mayor));

        }

        if(algoritmo=="Sharpening")
        {

                if(Img.channels()>=3)
                {

                hist_shrink(Img, datos,100,10);

                crear_imagen_BGR(&resultadoImg, Img.cols, Img.rows, datos,Img.channels());

                Img=image_sharp(resultadoImg);


                vector<Mat> channels;

                split(resultadoImg,channels); //split the image into channels

                equalizeHist(channels[0], channels[0]); //equalize histogram on the 1 channel

                equalizeHist(channels[1], channels[1]); //equalize histogram on the 2 channel

                equalizeHist(channels[2], channels[2]); //equalize histogram on the 3 channel


                merge(channels,resultadoImg); //merge 3 channels including the modified 1st channel into one image

                activateColor();
                }

                else
                {

                hist_shrink(Img, resultados,100,10);

                crear_imagen_niveles_gris(&resultadoImg, Img.cols, Img.rows, resultados);

                Img=image_sharp(resultadoImg);

                equalizeHist(Img, resultadoImg); //equalize histogram on the 1 channel

                activategray();
                }

                statusBar()->showMessage("Algoritmo "+ algoritmo +" aplicado");

        }

        if(algoritmo=="Mean_Filter")
        {
            dialogo18 = new Dialogo_Smooth();
            dialogo18->exec();
            int i = dialogo18->resultado();



                if(Img.channels()>=3)
                {

                blur(Img,resultadoImg,Size(i,i),Point(-1,-1));

                activateColor();
                }

                else
                {

                blur(Img,resultadoImg,Size(i,i),Point(-1,-1));

                activategray();
                }
                salida.append(QString::number(i));
                statusBar()->showMessage("Tamaño del kernel: " + QString::number(i));

        }
        if(algoritmo=="Median_Filter")
        {
            dialogo18 = new Dialogo_Smooth();
            dialogo18->exec();
            int i = dialogo18->resultado();

                if(Img.channels()>=3)
                {
                    medianBlur(Img,resultadoImg,i);

                activateColor();
                }

                else
                {
                    medianBlur(Img,resultadoImg,i);

                activategray();
                }

                salida.append(QString::number(i));
                statusBar()->showMessage("Tamaño del kernel: " + QString::number(i));

        }
        if(algoritmo=="Gaussian_Filter")
        {
            dialogo18 = new Dialogo_Smooth();
            dialogo18->exec();
            int i = dialogo18->resultado();

                if(Img.channels()>=3)
                {
                       GaussianBlur(Img,resultadoImg,Size(i,i),0,0);

                activateColor();
                }

                else
                {
                        GaussianBlur(Img,resultadoImg,Size(i,i),0,0);

                activategray();
                }

                salida.append(QString::number(i));
                statusBar()->showMessage("Tamaño del kernel: " + QString::number(i));

        }
        if(algoritmo=="Kuwahara_Filter")
        {
            dialogo19 = new Dialogo_Kuwahara();
            dialogo19->exec();
            int size = dialogo19->resultado();


                if(Img.channels()>=3)
                {
                resultadoImg=kuwahara_filter(Img,size);

                activateColor();
                }

                else
                {

                resultadoImg=kuwahara_filter_gray(Img,size);
                activategray();
                }

                salida.append(QString::number(size));
                statusBar()->showMessage("Tamaño de la ventana de filtrado: " + QString::number(size));

        }
        this->resize(800,600);
}

void subwindow::activategray()
{

    imageLabel->setPixmap(ASM::cvMatToQPixmap(resultadoImg));

    normalizarAct->setEnabled(true);
    manualAct->setEnabled(true);
    porcentualAct->setEnabled(true);
    histeresisAct->setEnabled(true);
    otsuAct->setEnabled(true);
    rosinAct->setEnabled(true);
    rosinNorAct->setEnabled(true);
    rosinNorAcuAct->setEnabled(true);
    proxiAct->setEnabled(true);
    proxiAcuAct->setEnabled(true);
    distAct->setEnabled(true);
    distAcuAct->setEnabled(true);
    menorAct->setEnabled(true);
    menorAcuAct->setEnabled(true);
    adapAct->setEnabled(true);
    adapAcuAct->setEnabled(true);
    semiAct->setEnabled(true);
    semiAcuAct->setEnabled(true);
    colorMapAct->setEnabled(true);

    lineargrayAct->setEnabled(true);
    slideAct->setEnabled(true);
    shrinkAct->setEnabled(true);
    stretchAct->setEnabled(true);
    adaptiveAct->setEnabled(true);
    highpassAct->setEnabled(true);
    highFrequencyAct->setEnabled(true);
    moravecAct->setEnabled(true);
    homomorphicAct->setEnabled(true);
    unsharpAct->setEnabled(true);
    sharpeningAct->setEnabled(true);
    meanFilterAct->setEnabled(true);
    medianFilterAct->setEnabled(true);
    gaussFilterAct->setEnabled(true);
    kuwaharaAct->setEnabled(true);

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    histogramAct->setEnabled(true);
    scaleFactor = 1.0;

    updateActions();

   if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

void subwindow::activateColor()
{

    imageLabel->setPixmap(ASM::cvMatToQPixmap(resultadoImg));

    leecockAct->setEnabled(true);
    scharcanskiAct->setEnabled(true);
    dvAct->setEnabled(true);
    dvhdAct->setEnabled(true);
    mvdagreAct->setEnabled(true);
    mvdcentralAct->setEnabled(true);
    shiozakiAct->setEnabled(true);
    pietiAct->setEnabled(true);

    lineargrayAct->setEnabled(true);
    slideAct->setEnabled(true);
    shrinkAct->setEnabled(true);
    stretchAct->setEnabled(true);
    adaptiveAct->setEnabled(true);
    highpassAct->setEnabled(true);
    highFrequencyAct->setEnabled(true);
    moravecAct->setEnabled(true);
    homomorphicAct->setEnabled(true);
    unsharpAct->setEnabled(true);
    sharpeningAct->setEnabled(true);
    meanFilterAct->setEnabled(true);
    medianFilterAct->setEnabled(true);
    gaussFilterAct->setEnabled(true);
    kuwaharaAct->setEnabled(true);

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    histogramAct->setEnabled(true);
    scaleFactor = 1.0;


    updateActions();

   if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

//Crea la ventana helpwindow (Manual de contenidos)
void subwindow::contents()
{
   helpwindow *other = new helpwindow;
   other->show();
}


void subwindow::about()
{
   QMessageBox::about(this, tr("Acerca de la aplicación"),
            tr("La <b>aplicación</b> muestra distintos tipos de procesamiento digital de imagenes ..."));
}



//Crea la venta histwindow (Histograma de la imagen)
void subwindow::histogram()
{
    if(umbral==0 && umbral_mayor==0 && umbral_menor==0)
    {
    histwindow *other = new histwindow(salida,resultadoImg);
    other->show();
    }
    else
    {
     if(umbral!=0)
        {
        histwindow *other = new histwindow(salida,resultadoImg,umbral);
        other->show();
        }
     else
        {
         histwindow *other = new histwindow(salida,resultadoImg,umbral_mayor,umbral_menor);
         other->show();
        }
    }
}


void subwindow::createActions()
{
//Acciones principales de la ventana

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Guardar"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Guarda la imagen al disco"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(tr("&Imprimir..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));


    closeAct = new QAction(tr("&Cerrar Ventana"), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Cierra esta ventana"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

//Histograma
    histogramAct = new QAction(QIcon(":/images/histogram.png"), tr("&Histograma"), this);
    histogramAct->setShortcut(tr("Ctrl+H"));
    histogramAct->setEnabled(false);
    histogramAct->setStatusTip(tr("Muestra el histograma de la imagen seleccionada"));
    connect(histogramAct, SIGNAL(triggered()), this, SLOT(histogram()));

//Normalizar
        normalizarAct = new QAction(tr("Normalizar imagen"), this);
        normalizarAct->setShortcut(tr("Ctrl+N"));
        normalizarAct->setEnabled(false);
        normalizarAct->setStatusTip(tr("Normaliza la imagen"));
        connect(normalizarAct, SIGNAL(triggered()), this, SLOT(normalizar2()));

//Acciones del visor de ventana
    zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), tr("Aumentar &Zoom (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    zoomInAct->setStatusTip(tr("Aumenta el zoom un 25% de la imagen seleccionada"));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), tr("Disminuir &Zoom (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    zoomOutAct->setStatusTip(tr("Disminuye el zoom un 25% de la imagen seleccionada"));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("Tamaño &Original"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(QIcon(":/images/zoom_best_fit.png"), tr("Ajustar a &Pantalla"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    fitToWindowAct->setStatusTip(tr("Ajusta la imagen a la pantalla"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

//Detección de bordes
    leecockAct = new QAction(tr("Algoritmo &Lee y Cock"), this);
    leecockAct->setEnabled(false);
    connect(leecockAct, SIGNAL(triggered()), this, SLOT(leecock()));

    scharcanskiAct = new QAction(tr("&Scharcanski-Venetsanopoulos"), this);
    scharcanskiAct->setEnabled(false);
    connect(scharcanskiAct, SIGNAL(triggered()), this, SLOT(scharcanski()));

    dvAct = new QAction(tr("&Dv"), this);
    dvAct->setEnabled(false);
    connect(dvAct, SIGNAL(triggered()), this, SLOT(dv()));

    dvhdAct = new QAction(tr("&Dv-Hv"), this);
    dvhdAct->setEnabled(false);
    connect(dvhdAct, SIGNAL(triggered()), this, SLOT(dvhd()));

    mvdagreAct = new QAction(tr("&Mvd agregadas mutuas"), this);
    mvdagreAct->setEnabled(false);
    connect(mvdagreAct, SIGNAL(triggered()), this, SLOT(mvdagre()));

    mvdcentralAct = new QAction(tr("&Mvd punto central"), this);
    mvdcentralAct->setEnabled(false);
    connect(mvdcentralAct, SIGNAL(triggered()), this, SLOT(mvdcentral()));

    shiozakiAct = new QAction(tr("&Shiozaki"), this);
    shiozakiAct->setEnabled(false);
    connect(shiozakiAct, SIGNAL(triggered()), this, SLOT(shiozaki()));

    pietiAct = new QAction(tr("&Pietikäinen-Rosenfeld"), this);
    pietiAct->setEnabled(false);
    connect(pietiAct, SIGNAL(triggered()), this, SLOT(pieti()));

//Umbralización
    manualAct = new QAction(tr("&Manual"), this);
    manualAct->setEnabled(false);
    connect(manualAct, SIGNAL(triggered()), this, SLOT(manual()));

    porcentualAct = new QAction(tr("&Porcentual"), this);
    porcentualAct->setEnabled(false);
    connect(porcentualAct, SIGNAL(triggered()), this, SLOT(porcentual()));

    histeresisAct = new QAction(tr("&Histéresis"), this);
    histeresisAct->setEnabled(false);
    connect(histeresisAct, SIGNAL(triggered()), this, SLOT(histeresis()));

    otsuAct = new QAction(tr("&Otsu"), this);
    otsuAct->setEnabled(false);
    connect(otsuAct, SIGNAL(triggered()), this, SLOT(otsu()));

    rosinAct = new QAction(tr("&Rosin"), this);
    rosinAct->setEnabled(false);
    connect(rosinAct, SIGNAL(triggered()), this, SLOT(rosin()));

    rosinNorAct = new QAction(tr("&Rosin normalizado"), this);
    rosinNorAct->setEnabled(false);
    connect(rosinNorAct, SIGNAL(triggered()), this, SLOT(rosinNor()));

    rosinNorAcuAct = new QAction(tr("&Rosin normalizado acumulado inverso"), this);
    rosinNorAcuAct->setEnabled(false);
    connect(rosinNorAcuAct, SIGNAL(triggered()), this, SLOT(rosinNorAcu()));

    proxiAct = new QAction(tr("&Próxim. (max/N,0.0)"), this);
    proxiAct->setEnabled(false);
    connect(proxiAct, SIGNAL(triggered()), this, SLOT(proxi()));

    proxiAcuAct = new QAction(tr("&Próxim. (max/N,0.0) acumulado inverso"), this);
    proxiAcuAct->setEnabled(false);
    connect(proxiAcuAct, SIGNAL(triggered()), this, SLOT(proxiAcu()));

    distAct = new QAction(tr("&Más dist. (1.0,1.0)"), this);
    distAct->setEnabled(false);
    connect(distAct, SIGNAL(triggered()), this, SLOT(dist()));

    distAcuAct = new QAction(tr("&Más dist. (1.0,1.0) acumulado inverso"), this);
    distAcuAct->setEnabled(false);
    connect(distAcuAct, SIGNAL(triggered()), this, SLOT(distAcu()));

    menorAct = new QAction(tr("&Menor dist. diagonal"), this);
    menorAct->setEnabled(false);
    connect(menorAct, SIGNAL(triggered()), this, SLOT(menor()));

    menorAcuAct = new QAction(tr("&Menor dist. diagonal acumulado inverso"), this);
    menorAcuAct->setEnabled(false);
    connect(menorAcuAct, SIGNAL(triggered()), this, SLOT(menorAcu()));

    adapAct = new QAction(tr("&Adaptativo"), this);
    adapAct->setEnabled(false);
    connect(adapAct, SIGNAL(triggered()), this, SLOT(adap()));

    adapAcuAct = new QAction(tr("&Adaptativo acumulado inverso"), this);
    adapAcuAct->setEnabled(false);
    connect(adapAcuAct, SIGNAL(triggered()), this, SLOT(adapAcu()));

    semiAct = new QAction(tr("&Semi-adaptativo"), this);
    semiAct->setEnabled(false);
    connect(semiAct, SIGNAL(triggered()), this, SLOT(semi()));

    semiAcuAct = new QAction(tr("&Semi-adaptativo acumulado inverso"), this);
    semiAcuAct->setEnabled(false);
    connect(semiAcuAct, SIGNAL(triggered()), this, SLOT(semiAcu()));

//Modificación escala de gris
    lineargrayAct = new QAction(tr("&Linear gray level modification (Mapping equation)"), this);
    lineargrayAct->setEnabled(false);
    connect(lineargrayAct, SIGNAL(triggered()), this, SLOT(lineargray()));

    slideAct = new QAction(tr("&Histogram slide"), this);
    slideAct->setEnabled(false);
    connect(slideAct, SIGNAL(triggered()), this, SLOT(slide()));

    shrinkAct = new QAction(tr("&Histogram shrink"), this);
    shrinkAct->setEnabled(false);
    connect(shrinkAct, SIGNAL(triggered()), this, SLOT(shrink()));

    stretchAct = new QAction(tr("&Histogram stretch"), this);
    stretchAct->setEnabled(false);
    connect(stretchAct, SIGNAL(triggered()), this, SLOT(stretch()));

    adaptiveAct = new QAction(tr("&Adaptive contrast filter"), this);
    adaptiveAct->setEnabled(false);
    connect(adaptiveAct, SIGNAL(triggered()), this, SLOT(adaptive()));

    colorMapAct = new QAction(tr("&ColorMap"), this);
    colorMapAct->setEnabled(false);
    connect(colorMapAct, SIGNAL(triggered()), this, SLOT(colorMap()));

//Nitidez
    highpassAct = new QAction(tr("&Highpass Filtering"), this);
    highpassAct->setEnabled(false);
    connect(highpassAct, SIGNAL(triggered()), this, SLOT(highpass()));

    highFrequencyAct = new QAction(tr("&High Frequency Emphasis"), this);
    highFrequencyAct->setEnabled(false);
    connect(highFrequencyAct, SIGNAL(triggered()), this, SLOT(highFrequency()));

    moravecAct = new QAction(tr("&Moravec Filter (Directional Difference Filters)"), this);
    moravecAct->setEnabled(false);
    connect(moravecAct, SIGNAL(triggered()), this, SLOT(moravec()));

    homomorphicAct = new QAction(tr("&Homomorphic Filtering"), this);
    homomorphicAct->setEnabled(false);
    connect(homomorphicAct, SIGNAL(triggered()), this, SLOT(homomorphic()));

    unsharpAct = new QAction(tr("&Unsharp Masking"), this);
    unsharpAct->setEnabled(false);
    connect(unsharpAct, SIGNAL(triggered()), this, SLOT(unsharp()));

    sharpeningAct = new QAction(tr("&Sharpening Algorithm"), this);
    sharpeningAct->setEnabled(false);
    connect(sharpeningAct, SIGNAL(triggered()), this, SLOT(sharpening()));

//Suavizado
    meanFilterAct = new QAction(tr("&Mean Filter"), this);
    meanFilterAct->setEnabled(false);
    connect(meanFilterAct, SIGNAL(triggered()), this, SLOT(meanFilter()));

    medianFilterAct = new QAction(tr("&Median Filter"), this);
    medianFilterAct->setEnabled(false);
    connect(medianFilterAct, SIGNAL(triggered()), this, SLOT(medianFilter()));

    gaussFilterAct = new QAction(tr("&Gaussian Filter"), this);
    gaussFilterAct->setEnabled(false);
    connect(gaussFilterAct, SIGNAL(triggered()), this, SLOT(gaussFilter()));

    kuwaharaAct = new QAction(tr("&Kuwahara Filter (Nonlinear Filtering)"), this);
    kuwaharaAct->setEnabled(false);
    connect(kuwaharaAct, SIGNAL(triggered()), this, SLOT(kuwahara()));

//Manual de ayuda
    contentsAct = new QAction(tr("Manual de &contenidos"), this);
    contentsAct->setStatusTip(tr("Muestra el manual de la aplicación"));
    contentsAct->setShortcut(tr("F1"));
    connect(contentsAct, SIGNAL(triggered()), this, SLOT(contents()));

    aboutAct = new QAction(tr("Sobre la &aplicación"), this);
    aboutAct->setStatusTip(tr("Muestra información sobre la aplicación"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

//Se crea la barra de menu
void subwindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Archivo"));
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    viewMenu = menuBar()->addMenu(tr("&Ver"));
    viewMenu->addAction(histogramAct);
    menuBar()->addSeparator();
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);
    menuBar()->addSeparator();
    viewMenu->addAction(normalizarAct);

    enhancementMenu = menuBar()->addMenu(tr("&Realce"));
    subenhancementMenu=enhancementMenu->addMenu(tr("Detector de &Bordes"));
    subenhancementMenu->addAction(leecockAct);
    subenhancementMenu->addAction(scharcanskiAct);
    subenhancementMenu->addAction(dvAct);
    subenhancementMenu->addAction(dvhdAct);
    subenhancementMenu->addAction(mvdagreAct);
    subenhancementMenu->addAction(mvdcentralAct);
    subenhancementMenu->addAction(shiozakiAct);
    subenhancementMenu->addAction(pietiAct);

    subenhancementMenu2=enhancementMenu->addMenu(tr("Modificación escala de Gris"));
    subenhancementMenu2->addAction(lineargrayAct);
    subenhancementMenu2->addAction(slideAct);
    subenhancementMenu2->addAction(shrinkAct);
    subenhancementMenu2->addAction(stretchAct);
    subenhancementMenu2->addAction(adaptiveAct);
    subenhancementMenu2->addAction(colorMapAct);


    subenhancementMenu3=enhancementMenu->addMenu(tr("Nitidez de la imagen"));
    subenhancementMenu3->addAction(highpassAct);
    subenhancementMenu3->addAction(highFrequencyAct);
    subenhancementMenu3->addAction(moravecAct);
    subenhancementMenu3->addAction(homomorphicAct);
    subenhancementMenu3->addAction(unsharpAct);
    subenhancementMenu3->addAction(sharpeningAct);

    subenhancementMenu4=enhancementMenu->addMenu(tr("Suavizado de la imagen"));
    subenhancementMenu4->addAction(meanFilterAct);
    subenhancementMenu4->addAction(medianFilterAct);
    subenhancementMenu4->addAction(gaussFilterAct);
    subenhancementMenu4->addAction(kuwaharaAct);

    menuBar()->addSeparator();

    thresholdingMenu= menuBar()->addMenu(tr("&Umbralización"));
    thresholdingMenu->addAction(manualAct);
    thresholdingMenu->addAction(porcentualAct);
    thresholdingMenu->addAction(histeresisAct);
    thresholdingMenu->addAction(otsuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(rosinAct);
    thresholdingMenu->addAction(rosinNorAct);
    thresholdingMenu->addAction(rosinNorAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(proxiAct);
    thresholdingMenu->addAction(proxiAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(distAct);
    thresholdingMenu->addAction(distAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(menorAct);
    thresholdingMenu->addAction(menorAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(adapAct);
    thresholdingMenu->addAction(adapAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(semiAct);
    thresholdingMenu->addAction(semiAcuAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Ayuda"));
    helpMenu->addAction(contentsAct);
    helpMenu->addAction(aboutAct);
}

//Se crea la barra de herramientas
void subwindow::createToolBars()
{

    fileToolBar = addToolBar(tr("Archivo"));
    fileToolBar->addAction(saveAct);

    viewToolBar = addToolBar(tr("Ver"));
    viewToolBar->addAction(histogramAct);
    viewToolBar->addAction(zoomInAct);
    viewToolBar->addAction(zoomOutAct);
    viewToolBar->addAction(fitToWindowAct);

}


void subwindow::createStatusBar()
{
    statusBar()->showMessage(tr("Listo"));
}


//Imprimir imagen
void subwindow::print()
{
    Q_ASSERT(imageLabel->pixmap());
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

//Funciones visor imagenes
void subwindow::zoomIn()
{
    scaleImage(1.25);
}


void subwindow::zoomOut()
{
    scaleImage(0.8);
}


void subwindow::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}


void subwindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}


void subwindow::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}


void subwindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}


void subwindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void subwindow::save()
{
  savefile(tr("Guardar imagen"), resultadoImg);
}



//Función para guardar imagen
void subwindow::savefile(const QString &titulo, Mat &imagen)
{

     QString escribir;

     escribir=salida;
     escribir.append(".jpg");
     QString fileName = QFileDialog::getSaveFileName(this, titulo, escribir, tr("Image Files (*.jpg *.jpeg)"));
     if (!fileName.isEmpty())
      {
        vector<int> parametros;
        parametros.push_back(CV_IMWRITE_JPEG_QUALITY);
        parametros.push_back(100);
        cv::imwrite(fileName.toStdString(), imagen, parametros);
      }
     else
           return;
}


//Funciones detector
void subwindow::leecock()
{
    subwindow *other = new subwindow(salida,"Lee-Cok",resultadoImg);
    other->show();

}

void subwindow::scharcanski()
{
    subwindow *other = new subwindow(salida,"Direccional",resultadoImg);
    other->show();
}

void subwindow::dv()
{
    subwindow *other = new subwindow(salida,"Dv",resultadoImg);
    other->show();
}

void subwindow::dvhd()
{
    subwindow *other = new subwindow(salida,"Dv-Hv",resultadoImg);
    other->show();
}

void subwindow::mvdagre()
{
    subwindow *other = new subwindow(salida,"Mvd-AM",resultadoImg);
    other->show();
}

void subwindow::mvdcentral()
{
    subwindow *other = new subwindow(salida,"Mvd-PC",resultadoImg);
    other->show();
}

void subwindow::shiozaki()
{
    subwindow *other = new subwindow(salida,"Shiozaki",resultadoImg);
    other->show();
}

void subwindow::pieti()
{
    subwindow *other = new subwindow(salida,"Pietikainen",resultadoImg);
    other->show();
}

//Funciones umbralización
void subwindow::manual()
{
    subwindow *other = new subwindow(salida,"Manual",resultadoImg);
    other->show();
}
void subwindow::porcentual()
{
    subwindow *other = new subwindow(salida,"Porcentual",resultadoImg);
    other->show();
}
void subwindow::histeresis()
{
    subwindow *other = new subwindow(salida,"Histeresis",resultadoImg);
    other->show();
}
void subwindow::otsu()
{
    subwindow *other = new subwindow(salida,"Otsu",resultadoImg);
    other->show();
}

void subwindow::rosin()
{
    subwindow *other = new subwindow(salida,"Rosin",resultadoImg);
    other->show();
}
void subwindow::rosinNor()
{
    subwindow *other = new subwindow(salida,"Rosin-Normalizado",resultadoImg);
    other->show();
}
void subwindow::rosinNorAcu()
{
    subwindow *other = new subwindow(salida,"Rosin-Normalizado_Acumulado_Inverso",resultadoImg);
    other->show();
}
void subwindow::proxi()
{
    subwindow *other = new subwindow(salida,"Proximidad",resultadoImg);
    other->show();
}
void subwindow::proxiAcu()
{
    subwindow *other = new subwindow(salida,"Proximidad_Acumulado_Inverso",resultadoImg);
    other->show();
}
void subwindow::dist()
{
    subwindow *other = new subwindow(salida,"Distancia",resultadoImg);
    other->show();
}
void subwindow::distAcu()
{
    subwindow *other = new subwindow(salida,"Distancia_Acumulado_Inverso",resultadoImg);
    other->show();
}
void subwindow::menor()
{
    subwindow *other = new subwindow(salida,"Diagonal",resultadoImg);
    other->show();
}
void subwindow::menorAcu()
{
    subwindow *other = new subwindow(salida,"Diagonal_Acumulado_Inverso",resultadoImg);
    other->show();
}
void subwindow::adap()
{
    subwindow *other = new subwindow(salida,"Adaptativo",resultadoImg);
    other->show();
}
void subwindow::adapAcu()
{
    subwindow *other = new subwindow(salida,"Adaptativo_Acumulado_Inverso",resultadoImg);
    other->show();
}
void subwindow::semi()
{
    subwindow *other = new subwindow(salida,"Semi-adaptativo",resultadoImg);
    other->show();
}
void subwindow::semiAcu()
{
    subwindow *other = new subwindow(salida,"Semi-adaptativo_Acumulado_Inverso",resultadoImg);
    other->show();
}
//Funciones realce
void subwindow::lineargray()
{
    subwindow *other = new subwindow(salida,"gray_Level",resultadoImg);
    other->show();
}

void subwindow::slide()
{
    subwindow *other = new subwindow(salida,"Histogram_Slide",resultadoImg);
    other->show();
}

void subwindow::shrink()
{
    subwindow *other = new subwindow(salida,"Histogram_Shrink",resultadoImg);
    other->show();
}

void subwindow::stretch()
{
    subwindow *other = new subwindow(salida,"Histogram_Stretch",resultadoImg);
    other->show();
}

void subwindow::adaptive()
{
    subwindow *other = new subwindow(salida,"Adaptive_Contrast",resultadoImg);
    other->show();
}

void subwindow::colorMap()
{
    subwindow *other = new subwindow(salida,"ColorMap",resultadoImg);
    other->show();
}

void subwindow::highpass()
{
    subwindow *other = new subwindow(salida,"Highpass_Filtering",resultadoImg);
    other->show();
}

void subwindow::highFrequency()
{
    subwindow *other = new subwindow(salida,"High_Frequency_Emphasis",resultadoImg);
    other->show();
}

void subwindow::moravec()
{
    subwindow *other = new subwindow(salida,"Moravec_Filter",resultadoImg);
    other->show();
}

void subwindow::homomorphic()
{
    subwindow *other = new subwindow(salida,"Homomorphic_Filtering",resultadoImg);
    other->show();
}

void subwindow::unsharp()
{
    subwindow *other = new subwindow(salida,"Unsharp_Masking",resultadoImg);
    other->show();
}

void subwindow::sharpening()
{
    subwindow *other = new subwindow(salida,"Sharpening",resultadoImg);
    other->show();
}

void subwindow::meanFilter()
{
    subwindow *other = new subwindow(salida,"Mean_Filter",resultadoImg);
    other->show();
}
void subwindow::medianFilter()
{
    subwindow *other = new subwindow(salida,"Median_Filter",resultadoImg);
    other->show();
}

void subwindow::gaussFilter()
{
    subwindow *other = new subwindow(salida,"Gaussian_Filter",resultadoImg);
    other->show();
}

void subwindow::kuwahara()
{
    subwindow *other = new subwindow(salida,"Kuwahara_Filter",resultadoImg);
    other->show();
}

void subwindow::normalizar2()
{
    subwindow *other = new subwindow(salida,"Normalizar",resultadoImg);
    other->show();
}

