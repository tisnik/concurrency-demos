;
;  (C) Copyright 2016, 2020  Pavel Tisnovsky
;
;  All rights reserved. This program and the accompanying materials
;  are made available under the terms of the Eclipse Public License v1.0
;  which accompanies this distribution, and is available at
;  http://www.eclipse.org/legal/epl-v10.html
;
;  Contributors:
;      Pavel Tisnovsky
;

(ns async5.core
  (:gen-class))

; nacteme vsechny potrebne funkce, makra a symboly z knihovny
; (schvalne se nenacitaji vsechny funkce, protoze by jejich jmena
;  prepsala takove zakladni funkce, jako je map apod.)
(require '[clojure.core.async :refer (go chan >! <! timeout alts!)])

(defn wait
  "Pozastaveni hlavniho vlakna - simulace interaktivni prace."
  []
  (Thread/sleep 10000))

(defn -main
  "Tato funkce se spusti automaticky nastrojem Leiningen."
  [& args]
  (println "Start")
  ; vytvorime kanaly
  (let [channel1 (chan)
        channel2 (chan)
        channel3 (chan)]

    ; kontinualni posilani zprav do trech kanalu v trojici asynchronnich bloku
    ; prvni kanal
    (go
        (doseq [i (range)]
            (<! (timeout 500))
            (>! channel1 i)))

    ; druhy kanal
    (go
        (doseq [i (range)]
            (<! (timeout 1000))
            (>! channel2 i)))

    ; treti kanal
    (go
        (doseq [i (range)]
            (<! (timeout 2000))
            (>! channel3 i)))

    (println "producers started")

    ; kontinualni cteni zprav z kanalu v asynchronnim bloku
    (go
        (while true
            (let [[item channel] (alts! [channel1 channel2 channel3])]
                (condp = channel
                    channel1 (println "channel #1: " item)
                    channel2 (println "channel #2: " item)
                    channel3 (println "channel #3: " item)))))

    (println "consumer started"))
  ; chvili pockame, az se vypise cela sekvence 0 az 9
  (wait)
  (println "Finish")
  (System/exit 0))

