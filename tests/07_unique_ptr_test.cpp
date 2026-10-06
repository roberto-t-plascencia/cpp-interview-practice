#include "07_unique_ptr.hpp"

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

namespace {

// Counts live instances so tests can detect leaks and double deletes.
struct Tracked {
    static inline int alive = 0;
    int value;
    std::string label;
    explicit Tracked(int v, std::string l = "") : value(v), label(std::move(l)) { ++alive; }
    ~Tracked() { --alive; }
};

class UniquePtrTest : public ::testing::Test {
protected:
    void SetUp() override { Tracked::alive = 0; }
};

}  // namespace

static_assert(!std::is_copy_constructible_v<UniquePtr<int>>, "must not be copyable");
static_assert(!std::is_copy_assignable_v<UniquePtr<int>>, "must not be copy-assignable");
static_assert(std::is_nothrow_move_constructible_v<UniquePtr<int>>, "move must be noexcept");
static_assert(!std::is_convertible_v<UniquePtr<int>, bool>, "operator bool must be explicit");

TEST_F(UniquePtrTest, DestructorDeletesObject) {
    {
        UniquePtr<Tracked> p(new Tracked(1));
        EXPECT_EQ(Tracked::alive, 1);
        EXPECT_EQ(p->value, 1);
        EXPECT_EQ((*p).value, 1);
    }
    EXPECT_EQ(Tracked::alive, 0);
}

TEST_F(UniquePtrTest, DefaultIsEmpty) {
    UniquePtr<Tracked> p;
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
}

TEST_F(UniquePtrTest, MoveConstructTransfersOwnership) {
    UniquePtr<Tracked> a(new Tracked(7));
    Tracked* raw = a.get();
    UniquePtr<Tracked> b(std::move(a));
    EXPECT_EQ(b.get(), raw);
    EXPECT_FALSE(a);  // NOLINT(bugprone-use-after-move): checking moved-from state
    EXPECT_EQ(Tracked::alive, 1);
}

TEST_F(UniquePtrTest, MoveAssignDeletesPreviousTarget) {
    UniquePtr<Tracked> a(new Tracked(1));
    UniquePtr<Tracked> b(new Tracked(2));
    b = std::move(a);
    EXPECT_EQ(Tracked::alive, 1);
    ASSERT_TRUE(b);
    EXPECT_EQ(b->value, 1);
    EXPECT_FALSE(a);  // NOLINT(bugprone-use-after-move)
}

TEST_F(UniquePtrTest, SelfMoveAssignIsSafe) {
    UniquePtr<Tracked> a(new Tracked(3));
    auto& alias = a;
    a = std::move(alias);
    ASSERT_TRUE(a);
    EXPECT_EQ(a->value, 3);
    EXPECT_EQ(Tracked::alive, 1);
}

TEST_F(UniquePtrTest, ReleaseGivesUpOwnershipWithoutDeleting) {
    UniquePtr<Tracked> p(new Tracked(5));
    Tracked* raw = p.release();
    EXPECT_FALSE(p);
    EXPECT_EQ(Tracked::alive, 1);
    delete raw;
    EXPECT_EQ(Tracked::alive, 0);
}

TEST_F(UniquePtrTest, ResetDeletesOldAndOwnsNew) {
    UniquePtr<Tracked> p(new Tracked(1));
    p.reset(new Tracked(2));
    EXPECT_EQ(Tracked::alive, 1);
    EXPECT_EQ(p->value, 2);
    p.reset();
    EXPECT_EQ(Tracked::alive, 0);
    EXPECT_FALSE(p);
}

TEST_F(UniquePtrTest, MakeUniqueForwardsArguments) {
    auto p = makeUnique<Tracked>(42, "answer");
    ASSERT_TRUE(p);
    EXPECT_EQ(p->value, 42);
    EXPECT_EQ(p->label, "answer");
}
