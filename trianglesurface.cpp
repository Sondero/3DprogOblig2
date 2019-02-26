#include "trianglesurface.h"

TriangleSurface::TriangleSurface(std::vector<float> aLocation, std::vector<float> bLocation, std::vector<float> cLocation)
{
    mVertices.push_back(Vertex(aLocation.at(0), aLocation.at(1), aLocation.at(2), 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(bLocation.at(0), bLocation.at(1), bLocation.at(2), 0.f, 0.f, 0.f));
    mVertices.push_back(Vertex(cLocation.at(0), cLocation.at(1), cLocation.at(2), 0.f, 0.f, 0.f));

    mMatrix.setToIdentity();
}

TriangleSurface::~TriangleSurface() {  }


void TriangleSurface::init(GLint matrixUniform) {
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

void TriangleSurface::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}
