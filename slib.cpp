#include "slib.h"


Vector3& Vector3::operator += (float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

Vector3& Vector3::operator -= (float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

Vector3& Vector3::operator *= (float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3& Vector3::operator /= (float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

Vector3 Vector3::operator - (float rhs) const
{
    Vector3 result = { x, y, z };
    return result -= rhs;
}

Vector3 Vector3::operator + (float rhs) const
{
    Vector3 result = { x, y, z };
    return result += rhs;
}

Vector3 Vector3::operator * (float rhs) const
{
    Vector3 result = { x, y, z };
    return result *= rhs;
}

Vector3 Vector3::operator / (float rhs) const
{
    Vector3 result = { x, y, z };
    return result /= rhs;
}

Vector3& Vector3::operator += (const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3& Vector3::operator -= (const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3& Vector3::operator *= (const Vector3& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3& Vector3::operator /= (const Vector3& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

Vector3 Vector3::operator - (const Vector3& rhs) const
{
    Vector3 result = { x, y, z };
    return result -= rhs;
}

Vector3 Vector3::operator + (const Vector3& rhs) const
{
    Vector3 result = { x, y, z };
    return result += rhs;
}

Vector3 Vector3::operator * (const Vector3& rhs) const
{
    Vector3 result = { x, y, z };
    return result *= rhs;
}

Vector3 Vector3::operator / (const Vector3& rhs) const
{
    Vector3 result = { x, y, z };
    return result /= rhs;
}

bool Vector3::operator == (const Vector3& rhs) const
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool Vector3::operator == (float rhs) const
{
    return x == rhs && y == rhs && z == rhs;
}

Vector3 Vector3::operator * (const Matrix& rhs) const
{
    Matrix lhs({{ this->x, this->y, this->z }});
    lhs *= rhs;
    return { lhs.data[0][0], lhs.data[0][1], lhs.data[0][2] };
}

Vector3 Vector3::operator *= (const Matrix& rhs)
{
    Matrix lhs({{ this->x, this->y, this->z }});
    lhs *= rhs;
    *this = { lhs.data[0][0], lhs.data[0][1], lhs.data[0][2] };
    return *this;
}

Matrix& Matrix::operator += (const Matrix& rhs)
{
    const auto rhsrows = rhs.data.size();
    const auto rhscols = rhs.data.at(0).size();
    const auto lhsrows = data.size();
    const auto lhscols = data.at(0).size();

    if (lhscols != rhsrows)
    {
        std::cout << "Error: Matrix-size mismatch." << std::endl;
        exit(1);
    }
    auto maxCols = lhscols >= rhscols ? lhscols : rhscols;
    for (int row = 0; row < static_cast<int>(lhsrows); ++row)
    {
        for (auto col = 0; col < static_cast<int>(maxCols); ++col)
        {
            data[row][col] += rhs.data[row][col];
        }
    }
    return *this;
}

Matrix& Matrix::operator *= (const Matrix& rhs)
{
    const auto rhsrows = rhs.data.size();
    const auto rhscols = rhs.data.at(0).size();
    const auto lhsrows = data.size();
    const auto lhscols = data.at(0).size();
    
    if (lhscols != rhsrows)
    {
        std::cout << "Error: Matrix-size mismatch." << std::endl;
        exit(1);
    }

    std::vector<std::vector<float>> result(lhsrows, std::vector<float>(rhscols, 0));

    for (size_t i = 0; i < lhsrows; ++i)
    {
        for (size_t j = 0; j < rhscols; ++j)
        {
            float cellValue = 0;
            for (size_t k = 0; k < lhscols; ++k)
            {
                cellValue += data[i][k] * rhs.data[k][j];
            }
            result[i][j] = cellValue;
        }
    }
    
    data = result;
    return *this;
}

Matrix Matrix::operator * (const Matrix& rhs) const
{
    Matrix toReturn(data);
    return toReturn *= rhs;
}

// TODO: This feels fragile. Figure out whether "Vector4 * Matrix" makes more sense than this.
Matrix Matrix::operator * (const Vector4& rhs) const
{
    Matrix rmatrix({{ rhs.vec.x, rhs.vec.y, rhs.vec.z, rhs.w  }});
    return rmatrix * *this;
}

Vector4 Vector4::operator * (const Matrix& rhs) const
{
    Matrix lhs({{ this->vec.x, this->vec.y, this->vec.z, this->w  }});
    lhs *= rhs;
    return { {lhs.data[0][0], lhs.data[0][1], lhs.data[0][2] }, lhs.data[0][3] };
}

Vector4 Vector4::operator *= (const Matrix& rhs)
{
    Matrix lhs({{ this->vec.x, this->vec.y, this->vec.z, this->w  }});
    lhs *= rhs;
    *this = { {lhs.data[0][0], lhs.data[0][1], lhs.data[0][2]}, lhs.data[0][3] };
    return *this;
}