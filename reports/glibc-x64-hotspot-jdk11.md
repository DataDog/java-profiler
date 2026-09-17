---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:55:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1789667463 79
1789667468 79
1789667473 79
1789667478 79
1789667483 79
1789667488 79
1789667493 79
1789667498 79
1789667503 79
1789667508 79
1789667513 96
1789667518 96
1789667523 96
1789667528 96
1789667533 96
1789667538 96
1789667543 96
1789667548 96
1789667553 96
1789667559 96
```
</details>

---

