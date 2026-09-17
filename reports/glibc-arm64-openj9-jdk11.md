---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 10 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 10 |
| Allocations | 175 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789680262 48
1789680267 46
1789680272 46
1789680277 46
1789680282 46
1789680287 46
1789680292 46
1789680297 46
1789680302 46
1789680307 46
1789680312 46
1789680317 48
1789680322 48
1789680327 48
1789680332 48
1789680337 48
1789680342 48
1789680347 48
1789680352 48
1789680357 48
```
</details>

---

