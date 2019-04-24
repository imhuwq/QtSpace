#include <iostream>

#include "VertexPack.h"
#include "VertexTable.h"
#include "Common/Files.h"
#include "FBXFileLoader.h"
#include "VertexContext.h"
#include "Resource/Scene.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

FBXFileLoader::FBXFileLoader() : root_node_(nullptr),
                                 fbx_manager_(nullptr),
                                 fbx_scene_(nullptr),
                                 model_file_("") {};

FBXFileLoader::~FBXFileLoader() = default;

NodePtr FBXFileLoader::Load(const string &file_path) {
    model_file_ = file_path;

    if (!InitializeSDK()) return nullptr;

    if (!ImportModelFile()) return nullptr ;

    if (!ParseModelFile()) return nullptr;

    DestroySDK();

    return root_node_;
}

bool FBXFileLoader::InitializeSDK() {
    fbx_manager_ = FbxManager::Create();
    FbxIOSettings *ios = FbxIOSettings::Create(fbx_manager_, IOSROOT);
    fbx_manager_->SetIOSettings(ios);
    fbx_scene_ = FbxScene::Create(fbx_manager_, "fbx_scene");
    return true;
}

bool FBXFileLoader::ImportModelFile() {
    FbxImporter *fbxImporter = FbxImporter::Create(fbx_manager_, "");

    bool status = fbxImporter->Initialize(model_file_.c_str(), -1, fbx_manager_->GetIOSettings());
    if (!status) {
        fbxImporter->Destroy();
        cerr << "FBXFileLoader::ImportModelFile: Fail to initialize importer." << endl;
        return status;
    }

    status = fbxImporter->Import(fbx_scene_);
    if (!status) {
        fbxImporter->Destroy();
        cerr << "FBXFileLoader::ImportModelFile: Fail to import file '" << model_file_ << "'." << endl;
        return status;
    }

    fbxImporter->Destroy();
    return true;
}

bool IsMeshNode(FbxNode *fbx_node) {
    FbxNodeAttribute *fbx_node_attribute = fbx_node->GetNodeAttribute();
    if (!fbx_node_attribute) return false;
    return fbx_node_attribute->GetAttributeType() == FbxNodeAttribute::eMesh && (bool) fbx_node->Visibility.Get();
}

FbxAMatrix ComputeTransformMatrix(FbxNode *pFbxNode) {
    FbxAMatrix transform_matrix = FbxAMatrix();

    auto *fbx_mesh = (FbxMesh *) pFbxNode->GetNodeAttribute();
    FbxAMatrix offset;
    FbxVector4 position = pFbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rotation = pFbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pFbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
    offset.SetT(position);
    offset.SetR(rotation);
    offset.SetS(scale);

    transform_matrix = offset;

    if (fbx_mesh->GetDeformerCount(FbxDeformer::eSkin) > 0) {
        FbxAMatrix skin_transform;
        auto *fbx_skin = (FbxSkin *) fbx_mesh->GetDeformer(0, FbxDeformer::eSkin);
        FbxCluster *fbx_cluster = fbx_skin->GetCluster(0);
        skin_transform = fbx_cluster->GetTransformMatrix(skin_transform);
        transform_matrix = skin_transform * offset;
    }

    return transform_matrix;
}

void CollectVertexPosition(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxVector4 *control_points = fbx_mesh->GetControlPoints();
    double *positions = control_points[context.vertex_index];
    positions = context.position_offset_matrix.MultT(positions);
    pack->positions = {(float) positions[0], (float) positions[1], (float) positions[2]};
}

void CollectVertexNormal(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementNormal *fbx_normal = fbx_mesh->GetElementNormal(0);
    if (!fbx_normal) return;

    FbxVector4 normal;
    bool found = fbx_mesh->GetPolygonVertexNormal(context.triangle_index, context.vertex_triangle_index, normal);
    if (found) pack->normals = {(float) normal[0], (float) normal[1], (float) normal[2]};
}

void CollectVertexUV0(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementUV *fbx_uv = fbx_mesh->GetElementUV(0);
    if (!fbx_uv) return;

    FbxVector2 uv;
    bool unmapped;
    bool found = fbx_mesh->GetPolygonVertexUV(context.triangle_index, context.vertex_triangle_index, fbx_uv->GetName(), uv, unmapped);
    if (found) pack->uv0 = {(float) uv[0], (float) uv[1]};
}

void CollectVertexUV1(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementUV *fbx_uv = fbx_mesh->GetElementUV(1);
    if (!fbx_uv) return;

    FbxVector2 uv;
    bool unmapped;
    bool found = fbx_mesh->GetPolygonVertexUV(context.triangle_index, context.vertex_triangle_index, fbx_uv->GetName(), uv, unmapped);
    if (found) pack->uv1 = {(float) uv[0], (float) uv[1]};
}

void CollectVertexColor(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementVertexColor *fbx_color = fbx_mesh->GetElementVertexColor(0);
    if (!fbx_color) return;

    FbxColor color;
    FbxGeometryElement::EMappingMode map_mode = fbx_color->GetMappingMode();
    int identifier;
    if (map_mode == FbxGeometryElement::eByPolygonVertex) identifier = context.vertex_id;
    else if (map_mode == FbxGeometryElement::eByControlPoint) identifier = context.vertex_index;
    else return;

    bool found = false;
    FbxGeometryElement::EReferenceMode ref_mode = fbx_color->GetReferenceMode();
    if (ref_mode == FbxGeometryElement::eDirect) {
        color = fbx_color->GetDirectArray().GetAt(identifier);
        found = true;
    } else if (ref_mode == FbxGeometryElement::eIndexToDirect) {
        int id = fbx_color->GetIndexArray().GetAt(identifier);
        color = fbx_color->GetDirectArray().GetAt(id);
        found = true;
    }

    if (found) pack->colors = {(float) (color.mRed), (float) (color.mGreen), (float) (color.mBlue), (float) (color.mAlpha)};
}

void CollectVertexTangent0(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementTangent *fbx_tangent = fbx_mesh->GetElementTangent(0);
    if (!fbx_tangent) return;

    FbxVector4 tangent;
    FbxGeometryElement::EMappingMode map_mode = fbx_tangent->GetMappingMode();
    int identifier;
    if (map_mode == FbxGeometryElement::eByPolygonVertex) identifier = context.vertex_id;
    else if (map_mode == FbxGeometryElement::eByControlPoint) identifier = context.vertex_index;
    else return;

    bool found = false;
    FbxGeometryElement::EReferenceMode ref_mode = fbx_tangent->GetReferenceMode();
    if (ref_mode == FbxGeometryElement::eDirect) {
        tangent = fbx_tangent->GetDirectArray().GetAt(identifier);
        found = true;
    } else if (ref_mode == FbxGeometryElement::eIndexToDirect) {
        int id = fbx_tangent->GetIndexArray().GetAt(identifier);
        tangent = fbx_tangent->GetDirectArray().GetAt(id);
        found = true;
    }

    if (found) { pack->tangent0 = {(float) tangent[0], (float) tangent[1], (float) tangent[2]}; }
}

void CollectVertexTangent1(VertexPackPtr &pack, FbxMesh *fbx_mesh, const VertexContext &context) {
    FbxGeometryElementTangent *fbx_tangent = fbx_mesh->GetElementTangent(1);
    if (!fbx_tangent) return;

    FbxVector4 tangent;
    FbxGeometryElement::EMappingMode map_mode = fbx_tangent->GetMappingMode();
    int identifier;
    if (map_mode == FbxGeometryElement::eByPolygonVertex) identifier = context.vertex_id;
    else if (map_mode == FbxGeometryElement::eByControlPoint) identifier = context.vertex_index;
    else return;

    bool found = false;
    FbxGeometryElement::EReferenceMode ref_mode = fbx_tangent->GetReferenceMode();
    if (ref_mode == FbxGeometryElement::eDirect) {
        tangent = fbx_tangent->GetDirectArray().GetAt(identifier);
        found = true;
    } else if (ref_mode == FbxGeometryElement::eIndexToDirect) {
        int id = fbx_tangent->GetIndexArray().GetAt(identifier);
        tangent = fbx_tangent->GetDirectArray().GetAt(id);
        found = true;
    }

    if (found) { pack->tangent1 = {(float) tangent[0], (float) tangent[1], (float) tangent[2]}; }
}

void FBXFileLoader::CollectFbxMeshInstanceData(FbxNode *fbx_node, NodePtr &parent_node) {
    string fbx_node_name = fbx_node->GetName();

    auto *fbx_mesh = (FbxMesh *) fbx_node->GetNodeAttribute();
    fbx_mesh->RemoveBadPolygons();
    fbx_mesh = (FbxMesh *) FbxGeometryConverter(fbx_manager_).Triangulate(fbx_mesh, true);
    fbx_mesh->GenerateNormals(false, true, false);
    fbx_mesh->GenerateTangentsDataForAllUVSets(true);

    VertexContext context;
    context.position_offset_matrix = ComputeTransformMatrix(fbx_node);
    context.controlpoint_count = fbx_mesh->GetControlPointsCount();
    context.triangle_count = fbx_mesh->GetPolygonCount();
    context.vertex_id = 0;

    VertexTable table(context.controlpoint_count);
    map<string, vector<unsigned int>> mesh_instances;

    for (int t_idx = 0; t_idx < fbx_mesh->GetPolygonCount(); t_idx++) {
        context.triangle_index = t_idx;
        context.triangle_buffer_indices = {};

        for (int v_idx = 0; v_idx < fbx_mesh->GetPolygonSize(t_idx); v_idx++) {
            context.vertex_triangle_index = v_idx;
            context.vertex_index = fbx_mesh->GetPolygonVertex(t_idx, v_idx);

            VertexPackPtr pack = make_shared<VertexPack>();
            CollectVertexPosition(pack, fbx_mesh, context);
            CollectVertexNormal(pack, fbx_mesh, context);
            CollectVertexUV0(pack, fbx_mesh, context);
            CollectVertexUV1(pack, fbx_mesh, context);
            CollectVertexColor(pack, fbx_mesh, context);
            CollectVertexTangent0(pack, fbx_mesh, context);
            CollectVertexTangent1(pack, fbx_mesh, context);

            table.Insert(pack, context);
            context.triangle_buffer_indices.push_back(context.buffer_index);
            context.vertex_id++;
        }

        int material_count = fbx_mesh->GetElementMaterialCount();
        if (material_count > 0) {
            string material_name = "default";
            FbxGeometryElementMaterial *fbx_material_element = fbx_mesh->GetElementMaterial(0);
            int material_id = fbx_material_element->GetIndexArray().GetAt(context.triangle_index);
            if (material_id >= 0) {
                FbxSurfaceMaterial *fbx_material = fbx_mesh->GetNode()->GetMaterial(material_id);
                material_name = fbx_material->GetName();
            }
            for (size_t i = 0; i < 3; i++) mesh_instances[material_name].push_back(context.triangle_buffer_indices[i]);
        } else {
            string material_name = fbx_mesh->GetNode()->GetName();
            for (size_t i = 0; i < 3; i++) mesh_instances[material_name].push_back(context.triangle_buffer_indices[i]);
        }
    }

    if (table.empty) return;

    vector<float> buffer;
    kVertexSemanticPtr semantic = table.Flatten(buffer);
    MeshPtr mesh = make_shared<Mesh>(buffer, semantic);

    for (auto &mesh_instance:mesh_instances) {
        string name = fbx_node_name + "_" + mesh_instance.first;
        MeshInstancePtr node = make_shared<MeshInstance>(name, mesh, nullptr, mesh_instance.second);
        parent_node->AddNode(node);
    }
}

NodePtr FBXFileLoader::CollectFbxNodeData(FbxNode *fbx_node) {
    string node_name = fbx_node->GetName();
    FbxAMatrix local_transform = fbx_node->EvaluateLocalTransform();
    FbxVector4 local_position = fbx_node->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 local_rotation = fbx_node->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 local_scale = fbx_node->GetGeometricScaling(FbxNode::eSourcePivot);
    NodePtr node = make_shared<Node>(node_name);
    node->Translate((float) local_position[0], (float) local_position[1], (float) local_position[2]);
    node->Rotate((float) local_rotation[0], (float) local_rotation[1], (float) local_rotation[2]);
    node->Scale((float) local_scale[0], (float) local_scale[1], (float) local_scale[2]);
    node->ComputeTransformation();

    if (IsMeshNode(fbx_node)) CollectFbxMeshInstanceData(fbx_node, node);
    return node;
}

void FBXFileLoader::WalkFbxNodeTree(FbxNode *fbx_node, NodePtr &parent_node) {
    NodePtr node = CollectFbxNodeData(fbx_node);
    parent_node->AddNode(node);

    for (int index = 0; index < fbx_node->GetChildCount(); index++) {
        FbxNode *fbx_child_node = fbx_node->GetChild(index);
        WalkFbxNodeTree(fbx_child_node, node);
    }
}

bool FBXFileLoader::ParseModelFile() {
    FbxNode *fbx_root_node = fbx_scene_->GetRootNode();
    root_node_ = CollectFbxNodeData(fbx_root_node);

    for (int index = 0; index < fbx_root_node->GetChildCount(); index++) {
        FbxNode *fbx_child_node = fbx_root_node->GetChild(index);
        WalkFbxNodeTree(fbx_child_node, root_node_);
    }
    return true;
}

void FBXFileLoader::DestroySDK() {
    fbx_scene_->Destroy();
    fbx_manager_->Destroy();
}
