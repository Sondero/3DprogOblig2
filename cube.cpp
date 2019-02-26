#include "cube.h"
#include "vertex.h"

Cube::Cube(std::vector<float> location)
{
/*
    float xAlternator = 1;
    float yAlternator = 1;
    float zAlternator = 1;

    for (int i = 0; i<8; i++)
    {
        points[i] = Vertex(location.at(0)+(0.5f*xAlternator), location.at(1)+(0.5f*yAlternator), location.at(2)+(0.5f*zAlternator), 0.f, 0.f, 0.f);

        xAlternator = xAlternator*-1.f;
        if (xAlternator > 0)
        {
            yAlternator = yAlternator*-1.f;

            if(yAlternator>0)
                zAlternator = zAlternator*-1.f;
        }
    }

    mVertices.push_back(points[0]);
    mVertices.push_back(points[1]);
    mVertices.push_back(points[2]);
*/
    mVertices.push_back(Vertex(0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(-0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(-0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f));



    mMatrix.setToIdentity();
}

Cube::~Cube() {

}


void Cube::init(GLint matrixUniform) {
   mMatrixUniform = matrixUniform;

   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

   glBindVertexArray(0);
}

void Cube::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}
