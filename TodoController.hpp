#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"
#include "../dto/Todo.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class TodoController : public oatpp::web::server::api::ApiController {
private:
	OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
	List<Object<TodoDto>> todos = List<Object<TodoDto>>::createShared();
public:
	TodoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{ }

	ENDPOINT("GET", "/todo/all", todosAll) {
		return ResponseFactory::createResponse(Status::CODE_200, todos, objectMapper);
	}

	ENDPOINT("GET", "/todo/{id}", todosOne, PATH(Int16, id)) {
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "������� �� �������!");
		}
		return ResponseFactory::createResponse(Status::CODE_200, todos[id], objectMapper);
	}

	ENDPOINT("POST", "/todo", todosAdd, BODY_DTO(Object<TodoDto>, todoDto)) {
		todos->push_back(todoDto);
		return ResponseFactory::createResponse(Status::CODE_201, todoDto, objectMapper);
	}
};

#include OATPP_CODEGEN_END(ApiController)
