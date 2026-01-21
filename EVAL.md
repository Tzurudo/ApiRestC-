# 📝 Feedback del ejercicio: API en C++

## 📄 `main.cpp`

### ✅ Lo bueno
- Arranque claro del servidor con mensaje explícito.
- Uso de `std::mutex` desde el inicio muestra conciencia de concurrencia.
- Separación de rutas mediante `register_user_routes` favorece la modularidad.

### ⚠️ Red flags
- Estado global (`users`, `next_id`, `mutex`) expuesto sin encapsulación → difícil de testear o reutilizar.
- No se verifica si `app.listen()` falla (puerto ocupado, permisos, etc.).

### 🛠️ Cómo mejorar
- Envuelve el estado en una clase o struct (`UserStore`) y pásalo a las rutas.
- Agrega verificación del resultado de `listen()`.

---

## 📄 `routes/users_routes.h`

### ✅ Lo bueno
- Rutas bien definidas con lambdas autocontenidas.
- Uso correcto de `std::lock_guard` en todos los accesos concurrentes.
- Validación previa a la manipulación de datos.
- Regex en rutas (`R"(/users/(\d+))"`) usada correctamente.
- Endpoint `/health` incluido → buena práctica operacional.

### ⚠️ Red flags
- `catch (...)` atrapa cualquier excepción, incluso errores no relacionados con JSON (ej: memoria).
- Búsqueda lineal en vector para `GET` y `DELETE` → no escala (O(n)).
- No se valida que `req.matches[1]` exista antes de `std::stoi` → posible crash.
- Dependencia directa de variables globales (`extern`) → alto acoplamiento.

### 🛠️ Cómo mejorar
- Atrapa solo `nlohmann::json::parse_error` en lugar de `...`.
- Considera `std::unordered_map<int, User>` para búsquedas O(1).
- Valida `req.matches.size() >= 2` antes de parsear el ID.
- Piensa cómo inyectar el almacenamiento en lugar de depender de globales.

---

## 📄 `models/User.h`

### ✅ Lo bueno
- Modelo simple y legible.
- `to_json` implementado correctamente → permite serialización automática.

### ⚠️ Red flags
- No hay `from_json` → obliga a parsear campos manualmente (más propenso a errores).
- Sin mecanismos para garantizar que un `User` siempre sea válido (ej: edad negativa).

### 🛠️ Cómo mejorar
- Agrega `from_json` para poder hacer `body.get<User>()`.
- Si el modelo crece, considera un constructor o función de fábrica que valide invariantes.

---

## 📄 `utils/response.h`

### ✅ Lo bueno
- Centraliza el formato de errores → consistencia en la API.
- Código minimalista y reutilizable.

### ⚠️ Red flags
- Nombre `json_error` limita su uso, pero no es crítico.

### 🛠️ Cómo mejorar
- Nada urgente. Si agregas respuestas exitosas genéricas después, podrías tener `json_response()` también.

---

## 📄 `utils/validation.h`

### ✅ Lo bueno
- Funciones pequeñas, puras y reutilizables.
- Validaciones básicas cubren casos mínimos necesarios.

### ⚠️ Red flags
- Validación de email muy laxa (`@` es insuficiente).
- Nombre vacío pasa si son solo espacios (`"   "`).
- Edad no tiene límite superior (¿200 años?).

### 🛠️ Cómo mejorar
- Para nombre: `!name.empty() && name.find_first_not_of(' ') != std::string::npos`.
- Para email: considera al menos `"@"` + `"."` después del `@`.
- Para edad: define un rango razonable (ej: `1 <= age <= 150`).

> 💡 **Importante**: estas validaciones son suficientes para un ejercicio. En producción, ajustarías según el dominio.

---

## 🧠 Mensaje final
  
Las observaciones anteriores no son “errores”, sino **señales de qué conceptos puedes profundizar** a medida que enfrentes sistemas más complejos o críticos (como en firmware).

¡Buen trabajo!