
# API REST en C++ con cpp-httplib

API REST básica implementada en **C++17** utilizando la librería header-only **cpp-httplib** y **nlohmann/json**, sin frameworks web ni base de datos. 
Los datos se almacenan en memoria.

---

## Requisitos

- Compilador compatible con **C++17**
- `g++` (recomendado)
- Sistema Linux / WSL / macOS

Las librerías utilizadas son **header-only**, no requieren instalación en el sistema.

---

## Estructura del proyecto

```

.
├── include/
│   ├── httplib.h
│   └── json.hpp
├── main.cpp
├── models/
│   └── User.h
├── routes/
│   └── users_routes.h
├── utils/
│   ├── response.h
│   └── validation.h
└── README.md

````

---

## Compilación

Desde la raíz del proyecto:

```bash
g++ -std=c++17 main.cpp -Iinclude -o api -pthread
````

---

## Ejecución

```bash
./api
```

El servidor se ejecuta en:

```
http://localhost:8080
```

---

## Endpoints

### Crear usuario

**POST** `/users`

```bash
curl -X POST http://localhost:8080/users \
-H "Content-Type: application/json" \
-d '{"name":"Juan","email":"juan@mail.com","age":25}'
```

Respuestas posibles:

* `201 Created`
* `400 Bad Request`

---

### Listar usuarios

**GET** `/users`

```bash
curl http://localhost:8080/users
```

---

### Obtener usuario por ID

**GET** `/users/{id}`

```bash
curl http://localhost:8080/users/1
```

Respuestas posibles:

* `200 OK`
* `404 Not Found`

---

### Eliminar usuario

**DELETE** `/users/{id}`

```bash
curl -X DELETE http://localhost:8080/users/1
```

Respuestas posibles:

* `204 No Content`
* `404 Not Found`

---

### Endpoint extra

**GET** `/health`

```bash
curl http://localhost:8080/health
```

Respuesta:

```json
{"status":"ok"}
```

---

## Validaciones

* `name`: no puede estar vacío
* `email`: debe contener `@`
* `age`: debe ser mayor a 0

Errores devueltos en formato JSON:

```json
{
  "error": "email inválido"
}
```

---

## Concurrencia

El acceso a los datos en memoria está protegido mediante `std::mutex` para evitar condiciones de carrera cuando se reciben múltiples requests simultáneos.
Esta solución es adecuada para una API simple y educativa, aunque no está pensada para alta escalabilidad.

---

## Notas finales

* No se utiliza base de datos
* No se utilizan frameworks web
* El enfoque principal es claridad, uso correcto de HTTP y diseño mantenible


# ApiRestC-
