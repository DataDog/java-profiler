---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 28-63 cores)</summary>

```
1789667408 28
1789667413 28
1789667418 28
1789667423 28
1789667428 28
1789667433 28
1789667438 63
1789667443 63
1789667448 63
1789667453 63
1789667458 43
1789667463 43
1789667468 43
1789667473 43
1789667478 43
1789667483 43
1789667488 43
1789667493 43
1789667498 43
1789667503 43
```
</details>

---

