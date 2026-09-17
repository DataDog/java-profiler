---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:31:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1789680272 33
1789680277 33
1789680282 33
1789680287 33
1789680292 33
1789680297 33
1789680302 33
1789680307 33
1789680312 33
1789680317 33
1789680322 33
1789680327 33
1789680332 33
1789680337 33
1789680342 33
1789680347 33
1789680352 33
1789680357 33
1789680362 33
1789680367 33
```
</details>

---

