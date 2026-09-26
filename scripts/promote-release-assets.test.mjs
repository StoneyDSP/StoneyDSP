import assert from "node:assert/strict";
import { test } from "node:test";

import { planAssetPromotion } from "./promote-release-assets.mjs";

const local = [
  { name: "one.tar.gz", path: "/one.tar.gz", digest: "a".repeat(64) },
  { name: "two.zip", path: "/two.zip", digest: "b".repeat(64) },
];

test("uploads only missing assets and skips identical assets", async () => {
  const plan = await planAssetPromotion(
    local,
    [{ id: 1, name: "one.tar.gz", digest: `sha256:${"a".repeat(64)}`, url: "unused" }],
    async () => {
      throw new Error("digest download should not be needed");
    },
  );

  assert.deepEqual(plan.skip, ["one.tar.gz"]);
  assert.deepEqual(plan.upload, [local[1]]);
});

test("downloads an existing asset when GitHub has no digest", async () => {
  const plan = await planAssetPromotion(
    [local[0]],
    [{ id: 1, name: "one.tar.gz", url: "asset-url" }],
    async (asset) => {
      assert.equal(asset.url, "asset-url");
      return "a".repeat(64);
    },
  );

  assert.deepEqual(plan.skip, ["one.tar.gz"]);
  assert.deepEqual(plan.upload, []);
});

test("rejects conflicts before returning an upload plan", async () => {
  await assert.rejects(
    planAssetPromotion(
      local,
      [{ id: 1, name: "one.tar.gz", digest: `sha256:${"c".repeat(64)}`, url: "unused" }],
      async () => "unused",
    ),
    /already exists with different content.*No assets were uploaded/,
  );
});
