#include "MassSpringSystem.h"

MASS_SPRING_SYSTEM::MASS_SPRING_SYSTEM(
    int maxParticles,
    int maxSprings)
{
	defaultStiffness = 500;
	defaultlDistance = 12;
    init(maxParticles, maxSprings);
}

void MASS_SPRING_SYSTEM::init(
    int maxParticles,
    int maxSprings
) {
    m_Gravity = Vector3(0.0, -9.8, 0.0);
    m_FlgCollisionConstraints = false;

    m_MaxParticles = maxParticles;
    m_CurParticles = 0;
    mParticles = new PARTICLE[m_MaxParticles];
    //
    m_MaxSprings = maxSprings;
    m_CurSprings = 0;
    mSprings = new SPRING[m_MaxSprings];
}
void MASS_SPRING_SYSTEM::setSphereArrangementParams(int m_NumCircles, int m_NumSamples)
{
	this->m_NumCircles = m_NumCircles;
	this->m_NumSamples = m_NumSamples;
	std::cout<<m_NumCircles<<" spheres in each line and "<<m_NumSamples<<" rows of spheres"<<std::endl; 
}
int MASS_SPRING_SYSTEM::addParticle(SceneNode *n, Real radius, bool movable)
{
	//not sure about the mass, what should we set there? 
	mParticles[m_CurParticles].snode = n;
	mParticles[m_CurParticles].radius = radius;
	mParticles[m_CurParticles].movable = movable;
	//mParticles[m_CurParticles].velocity = Vector3(0,0,0);
	//mParticles[m_CurParticles].f = mParticles[m_CurParticles].velocity
	
	m_CurParticles++;
 
    return 0;
    
}

int MASS_SPRING_SYSTEM::addSpring(
    int n0, int n1)
{
   // SPRING *s = new SPRING;
	SPRING *s = &mSprings[m_CurSprings];
	s->n0 = n0;
	s->n1 = n1;
	s->L0 = (n1-n0 == 2*m_NumSamples)?2*defaultlDistance:defaultlDistance;
	m_CurSprings++;
	return 0;
}
int MASS_SPRING_SYSTEM::initSprings(int mSpheresNum){
	int index0, index1;
	int counter =0;
	//setting up for adjacent springs
	for(int i=0; i<m_NumCircles-1; i++){
		index0 = i*m_NumSamples;
		index1 = (i+1)*m_NumSamples;
		if(index0%(m_NumCircles-1) == 0)continue;
		for(int j=0;j<m_NumSamples;j++, index0++, index1++){
			//mSprings[counter] = addSpring(index0, index1);
			mSprings[counter].n0 = index0;
			mSprings[counter].n1 = index1;
			mSprings[counter].L0 = 
			counter++;
			std::cout<<"added string between "<<index0<<", "<<index1<<std::endl;
		}
	} 
	//for springs one and over 
	
	for(int i=0; i < m_NumCircles-1; i++){
		index0 = m_NumSamples*i;
		index1 = m_NumSamples*(i+2);
		if(index0%(m_NumCircles-1)==0)continue;
		for(int j=0; j<m_NumSamples; j++, index0++, index1++){
			if(index0 >104)break; //so that we don't assign string to the last row
			mSprings[counter].n0 = index0;
			mSprings[counter].n1 = index1;
			counter++;
			std::cout<<"added string between "<<index0<<", "<<index1<<std::endl;
		}
	}
	m_CurSprings = counter;
	return 1;
}
void MASS_SPRING_SYSTEM::setGravity(const Vector3 &g)
{
    m_Gravity = g;
}

//
// reset force
// compute damping force
// compute viscous damping force between particles
// compute spring force
// compute net force
/*
calculate the viscous force now 
*/
void MASS_SPRING_SYSTEM::computeForce(float time_step)
{
	//reset the force after every iteration
	for(int i=0; i<m_CurParticles; i++){
		mParticles[i].f = Vector3::ZERO; 
		mParticles[i].f += mParticles[i].mass *m_Gravity; //g = m*w
		
	}
	
	float kd = 0.025;
	float ks = 0.15;
	for(int i=0; i<m_CurSprings; i++){
		int index0 = mSprings[i].n0;
		int index1 = mSprings[i].n1;
		if(index0< 8){
			mParticles[index0].velocity = Vector3::ZERO;	
		}
		if(index1<8){
			mParticles[index1].velocity = Vector3::ZERO;
		}
		Vector3 p0 = mParticles[index0].snode->getPosition();
		Vector3 p1 = mParticles[index1].snode->getPosition();
		Vector3 p0p1 = (p1-p0);
		Real d = p0.distance(p1);
		p0p1.normalise();
		Vector3 F = defaultStiffness*( d - mSprings[i].L0)*p0p1;
		//std::cout<<"force so far: "<<F<<std::endl;
		mParticles[index0].f += F;
		mParticles[index1].f += -F;
		Vector3 vF;
		Vector3 v0 = mParticles[index0].velocity;
		Vector3 v1 = mParticles[index1].velocity;
		vF = -ks*(v1-v0);
		//mParticles[index0].f += vF;
		//mParticles[index1].f += -vF;
		mParticles[index0].f += -kd*(mParticles[index0].velocity);
		//std::cout<<"computing the Force "<<mParticles[inde].f<<std::endl;
		//std::cout<<"computing the forces "<<mParticles[index0].f<<" "<<mParticles[index1].f<<std::endl;
		
	}
	
}

void MASS_SPRING_SYSTEM::computeVelocity(float time_step)
{
	for(int i=0; i<m_CurParticles; i++){
		Vector3 v = mParticles[i].velocity;
		v = v + (mParticles[i].f/mParticles[i].mass)*time_step;
		v.x = (v.x > 50)?50:v.x;
		v.y = (v.y > 50)?50:v.y;
		v.z = (v.z > 50)?50:v.z;
		mParticles[i].velocity = v;
		//std::cout<<"v: "<<v<<std::endl;
		//std::cout<<"velocity "<<i<<" "<<v<<" position: "<<mParticles[i].snode->getPosition()<<
		//	"force "<<mParticles[i].f<<std::endl;
	}
}

void MASS_SPRING_SYSTEM::computePosition(float time_step)
{
	int mNumSpheres = m_NumSamples * m_NumCircles;
	for(int i=0; i<m_CurParticles; i++){
		 if(!mParticles[i].movable){
			mParticles[i].velocity =0;
			//mParticles[i].f =0;
			//std::cout<<"skipping over: "<<i<<std::endl;
		}
		if(mParticles[i].movable){
			Vector3 p = mParticles[i].snode->getPosition();
			Vector3 v = mParticles[i].velocity;
			//std::cout<<"v: "<<v<<" p: "<<p<<std::endl;
			p = p + v*time_step;
			mParticles[i].snode->setPosition(p);
		}
	}
}

void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint_Floor(float time_step)
{
	float e = 0.05;
	float small_radius = 5.0;
	for(int i=0; i<m_CurParticles; i++){
		Vector3 p = mParticles[i].snode->getPosition();
		if(p.y < small_radius){
			std::cout<<"setting new position"<<std::endl;
			p.y = e + small_radius;
			mParticles[i].snode->setPosition(p);
		}
		
	}
}

void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint_LargeSphere(float time_step)
{
    float large_radius = 100.0;
    float small_radius = 5.0;
    float e = 0.05;
	float total_radius = (large_radius + small_radius + e) * (large_radius + small_radius + e);
	for(int i=0; i < m_CurParticles; i++){
		Vector3 p0 = mParticles[i].snode->getPosition();
		Vector3 p1 = Vector3::ZERO; //the origin vector
		Vector3 p0p1 = p0- p1;
			p0p1.normalise();
			if(p0.squaredDistance(p1) < total_radius + 2*e){
				if(p0p1.dotProduct(mParticles[i].velocity) < 0){
					Vector3 v = mParticles[i].velocity;
					Vector3 v1 = v;
					v = v1 - (p0p1.dotProduct(v))*p0p1;
					mParticles[i].velocity = v;
				}
			}
	}
}
void MASS_SPRING_SYSTEM::computeRegularCollision_LargeSphere(float time_step)
{
	float large_radius = 100.0;
	float small_radius = 5.0;
	float e = 0.05;
	Vector3 max = Vector3(100, 100, 100);
	float totalRadius = (large_radius + small_radius + e)*(large_radius + small_radius +e);
	Vector3 origin = Vector3::ZERO;
	for(int i =0; i<m_CurParticles; i++){
		Vector3 p = mParticles[i].snode->getPosition();
		Vector3 p0p1 = p-origin + e;
		if(p.squaredDistance(origin) < totalRadius){
			p0p1.normalise();
			mParticles[i].snode->translate(p0p1);
		}
		
	}
}
void MASS_SPRING_SYSTEM::computeRegularCollision_Floor(float time_step)
{
	float e = 0.05;
	float small_radius = 5.0f;
	for(int i =0; i<m_CurParticles; i++){
		Vector3 p = mParticles[i].snode->getPosition();
		if(p.y < small_radius){
			p.y =  e + small_radius ;
			mParticles[i].snode->setPosition(p);
		}
		
	}
}
void MASS_SPRING_SYSTEM::computeRegularCollision(float time_step){
	//first computing the regular collision of all balls with each other
	float small_radius = 5.0;
	float e = 0.05;
	float totalRadius = (2*small_radius +e)*(2*small_radius + e);
	//std::cout<<"regular collision"<<std::endl;
	/*
	for(int i=0; i < m_CurParticles; i++){
		Vector3 p0 = mParticles[i].snode->getPosition();
		
		for(int j=i+1; j<m_CurParticles; j++){	
			Vector3 p1 = mParticles[j].snode->getPosition();
			Vector3 p0p1 = p1-p0;
			if( p0.squaredDistance(p1) < totalRadius){
				p0p1.normalise();
				mParticles[j].snode->translate(p0p1);
			}
		}
	}
	*/
	computeRegularCollision_LargeSphere( time_step);
	computeRegularCollision_Floor( time_step);
}
void MASS_SPRING_SYSTEM::adjustVelocityDueToCollisionConstraint(float time_step)
{ 
	//calculate the collision between any two different spheres
	/*
	float small_radius = 5;
	float e = 0.05;
	float total_radius = (2*small_radius + e)*(2*small_radius + e);
	for(int i=0; i< m_CurParticles; i++){
		Vector3 p0 = mParticles[i].snode->getPosition();
		for(int j=i+1; j< m_CurParticles; j++){
			Vector3 p1 = mParticles[j].snode->getPosition();
			if(p1.squaredDistance(p0) < total_radius){
				Vector3 p0p1 = p1-p0;
				p0p1.normalise();
				Vector3 vj = mParticles[j].velocity;
				if(p0p1.dotProduct(mParticles[j].velocity) > 0){
					vj = vj - (p0p1.dotProduct(vj))*p0p1;
					mParticles[j].velocity = vj;
					
				}
				Vector3 vi = mParticles[i].velocity;
				if(p0p1.dotProduct(mParticles[j].velocity) < 0){
					vi = vi + (p0p1.dotProduct(vi))*p0p1;
					mParticles[i].velocity = vi;
				}
			}
		}
	}
	*/
    adjustVelocityDueToCollisionConstraint_Floor(time_step);
    adjustVelocityDueToCollisionConstraint_LargeSphere(time_step);
}

void MASS_SPRING_SYSTEM::reset()
{
    resetVelocity();
}

void MASS_SPRING_SYSTEM::resetVelocity()
{
    if (m_CurParticles < 0) return;
	//std::cout<<"resetting velocity"<<std::endl;
    for (int i = 0; i < m_CurParticles; ++i ) {
        PARTICLE *p = &mParticles[i];
        p->velocity = Vector3::ZERO;
    }
}

void MASS_SPRING_SYSTEM::setCollisionConstraint(bool enable)
{
    m_FlgCollisionConstraints = enable;
}
//if it doesn't work, change the velocity to be called before the collison
void MASS_SPRING_SYSTEM::update(float time_step) {
    computeForce(time_step);
	
	if (m_FlgCollisionConstraints)adjustVelocityDueToCollisionConstraint(time_step);
	else{computeRegularCollision(time_step);}
	 computeVelocity(time_step);
	//adjustVelocityDueToCollisionConstraint(time_step);
	computePosition(time_step);
}