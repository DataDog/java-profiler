---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1789667438 28
1789667443 28
1789667448 28
1789667453 28
1789667458 59
1789667463 59
1789667468 59
1789667473 59
1789667478 59
1789667483 59
1789667488 59
1789667493 59
1789667498 59
1789667503 59
1789667508 59
1789667513 59
1789667518 59
1789667523 59
1789667528 59
1789667533 59
```
</details>

---

