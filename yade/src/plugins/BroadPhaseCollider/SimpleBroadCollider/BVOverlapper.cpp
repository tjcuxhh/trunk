#include "BVOverlapper.hpp"
#include "BoundingSphere.hpp"
#include "AABB.hpp"

BVOverlapper::BVOverlapper () : Overlapper()
{
	addPair((new BoundingSphere())->type,(new BoundingSphere())->type, &overlappSphereSphere,NULL);
	addPair((new BoundingSphere())->type,(new AABB())->type, &overlappSphereAABB,&overlappAABBSphere);	
	addPair((new AABB())->type,(new AABB())->type, &overlappAABBAABB,NULL);
}

BVOverlapper::~BVOverlapper ()
{

}

void BVOverlapper::registerAttributes()
{

}
void BVOverlapper::processAttributes()
{

}
bool BVOverlapper::overlappSphereSphere(const shared_ptr<BoundingVolume> bv1, const shared_ptr<BoundingVolume> bv2)
{
	shared_ptr<BoundingSphere> s1 = shared_dynamic_cast<BoundingSphere>(bv1);
	shared_ptr<BoundingSphere> s2 = shared_dynamic_cast<BoundingSphere>(bv2);
	
	return ((s1->center-s2->center).length()<s1->radius+s2->radius);
	
}

bool BVOverlapper::overlappAABBSphere(const shared_ptr<BoundingVolume> bv1, const shared_ptr<BoundingVolume> bv2)
{

	Vector3 l,t,p,q,r;
	bool onborder = false;
	Vector3 pt1,pt2,normal;
	float depth;
	
	shared_ptr<BoundingSphere> s = shared_dynamic_cast<BoundingSphere>(bv2);
	shared_ptr<AABB> aabb = shared_dynamic_cast<AABB>(bv1);
	
	p = s->center-aabb->center;
	
	l[0] = aabb->halfSize[0];
	t[0] = p[0]; 
	if (t[0] < -l[0]) { t[0] = -l[0]; onborder = true; }
	if (t[0] >  l[0]) { t[0] =  l[0]; onborder = true; }

	l[1] = aabb->halfSize[1];
	t[1] = p[1];
	if (t[1] < -l[1]) { t[1] = -l[1]; onborder = true; }
	if (t[1] >  l[1]) { t[1] =  l[1]; onborder = true; }

	l[2] = aabb->halfSize[2];
	t[2] = p[2];
	if (t[2] < -l[2]) { t[2] = -l[2]; onborder = true; }
	if (t[2] >  l[2]) { t[2] =  l[2]; onborder = true; }

	if (!onborder) 
		return true;

	q = t;
	
	r = p - q;
	
	depth = s->radius-sqrt(r.dot(r));
	
	return (depth >= 0);
	
}


bool BVOverlapper::overlappAABBAABB(const shared_ptr<BoundingVolume> bv1, const shared_ptr<BoundingVolume> bv2)
{
	Vector3 min1 = bv1->min;
	Vector3 max1 = bv1->max;
	Vector3 min2 = bv2->min;
	Vector3 max2 = bv2->max;
	
	return !(max1[0]<min2[0] || max2[0]<min1[0] || max1[1]<min2[1] || max2[1]<min1[1] || max1[2]<min2[2] || max2[2]<min1[2]);
}


	

