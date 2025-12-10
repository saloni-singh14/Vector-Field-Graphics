# Vector-Field-Graphics

## Vector Fields with Lines
We visualize different vector fields using **Bresenham's Line Drawing Algorithm**.  
Each vector has its tail at (x1, y1) and its head at:

    (x1 + f(x1), y1 + f(y1))

### F(x, y) = (y, -x)
![lineVectorField1](https://github.com/user-attachments/assets/68c580bd-2db8-4411-8b27-15ff9d51f974)

### F(x, y) = (x, y)
![lineVectorField2](https://github.com/user-attachments/assets/85e658d8-89f5-4acb-abd7-ef64c44d15d2)

### F(x, y) = (x, y) — Colourful
![lineVectorField2Colour](https://github.com/user-attachments/assets/07357003-f98b-4d26-bfa7-9cf4d5a703bc)

### F(x, y) = (y, x)
![lineVectorField3](https://github.com/user-attachments/assets/454d156b-4b89-4ea5-b55a-4fd54d59a81a)

---

## Vector Fields with Circles

We visualize vector fields using **circles** representing the vectors.  
The centre of each circle is the vector tail, and the radius is proportional to the vector magnitude.

### F(x, y) = (const, const)  
where:

    const = step / (2 * sqrt(2))

![circleVectorField1](https://github.com/user-attachments/assets/9e887624-8bdf-4dde-8a29-8fa5524024be)

---

### F(x, y) = (const, const)  
where:

    const = step / 2

![circleVectorField3](https://github.com/user-attachments/assets/9736dea3-92aa-4709-8a79-5d8495202b8d)

---

### F(x, y) = (const / sqrt(x^2 + y^2), const / sqrt(x^2 + y^2))
![circleVectorField4](https://github.com/user-attachments/assets/1e3a7a9c-db29-4db3-92f6-cf78008a325b)

---

### F(x, y) = (const * sin(x), 0)
![circleVectorField5](https://github.com/user-attachments/assets/3b292c42-0fd0-4ca0-a552-4c7a6f40f8d2)
