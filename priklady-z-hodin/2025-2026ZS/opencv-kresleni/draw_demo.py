import cv2
import numpy as np

def main():
    # 1. Inicializace kamery
    cap = cv2.VideoCapture(0)
    
    # Nastavení rozlišení
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

    # 2. Definice rozsahu pro jasně žlutou barvu v HSV
    yellow_lower = np.array([20, 100, 100])
    yellow_upper = np.array([30, 255, 255])

    # 3. Inicializace plátna
    canvas = None
    
    # Body pro kreslení
    prev_point = None
    drawing_color = (255, 255, 255)
    
    # Parametry pro vyhlazování (Exponential Moving Average)
    smoothed_point = None
    alpha = 0.2 # Koeficient vyhlazování (0.1 - velmi plynulé/zpožděné, 0.9 - syrové/třesavé)

    print("--- Vylepšená Virtuální Tabule ---")
    print("Ovládání:")
    print(" 'c' - Vymazat plátno")
    print(" 'q' - Ukončit program")

    window_name = "Virtual Glass Table"
    cv2.namedWindow(window_name)

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Zrcadlové otočení obrazu
        frame = cv2.flip(frame, 1)
        
        # Inicializace plátna při prvním snímku
        if canvas is None:
            canvas = np.zeros_like(frame)

        # 4. Detekce žluté barvy s vysokou přesností
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv, yellow_lower, yellow_upper)
        
        # Morfologické operace pro potlačení šumu a spojení objektu
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

        # 5. Hledání obrysů
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        raw_point = None

        if contours:
            # Najdeme největší objekt
            largest_contour = max(contours, key=cv2.contourArea)
            
            if cv2.contourArea(largest_contour) > 800:
                # Najdeme nejvyšší bod obrysu přesnějším způsobem
                # Procházíme body obrysu a hledáme ten s minimální Y souřadnicí
                top_idx = np.argmin(largest_contour[:, :, 1])
                raw_point = tuple(largest_contour[top_idx][0])

                # --- VYLEPŠENÍ: Vyhlazování (Smoothing) ---
                if smoothed_point is None:
                    smoothed_point = np.array(raw_point, dtype=float)
                else:
                    # EMA: New = alpha * Target + (1-alpha) * Old
                    curr_raw = np.array(raw_point, dtype=float)
                    smoothed_point = alpha * curr_raw + (1 - alpha) * smoothed_point
                
                display_point = (int(smoothed_point[0]), int(smoothed_point[1]))

                # Dynamické vzorkování barvy ze středu
                m = cv2.moments(largest_contour)
                if m["m00"] != 0:
                    cx = int(m["m10"] / m["m00"])
                    cy = int(m["m01"] / m["m00"])
                    drawing_color = tuple(map(int, frame[cy, cx]))

                # Indikátor špičky
                cv2.circle(frame, display_point, 7, (0, 255, 255), -1)

                # 6. Kreslení na plátno (používáme vyhlazené body)
                if prev_point is not None:
                    cv2.line(canvas, prev_point, display_point, drawing_color, 7)
                
                prev_point = display_point
            else:
                prev_point = None
                smoothed_point = None
        else:
            prev_point = None
            smoothed_point = None

        # 7. Spojení videa a plátna
        frame_with_drawing = cv2.addWeighted(frame, 1, canvas, 0.8, 0)

        # Zobrazení
        cv2.imshow(window_name, frame_with_drawing)

        # 8. Ovládání
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') or cv2.getWindowProperty(window_name, cv2.WND_PROP_VISIBLE) < 1:
            break
        elif key == ord('c'):
            canvas = np.zeros_like(frame)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
