---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 40-43 cores)</summary>

```
1789995341 42
1789995346 40
1789995351 40
1789995356 40
1789995361 40
1789995366 40
1789995371 40
1789995376 40
1789995381 40
1789995386 40
1789995391 40
1789995396 40
1789995401 40
1789995406 40
1789995411 40
1789995416 43
1789995421 43
1789995426 40
1789995431 40
1789995436 40
```
</details>

---

