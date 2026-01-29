---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 07:01:52 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 18.97/sec |
| Health Score | 1186% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 28.47/sec |
| Health Score | 1779% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769687531 32
1769687536 32
1769687541 32
1769687546 32
1769687551 32
1769687556 32
1769687561 32
1769687566 32
1769687571 32
1769687576 32
1769687581 32
1769687586 32
1769687591 32
1769687596 32
1769687601 32
1769687606 30
1769687611 30
1769687616 30
1769687621 30
1769687626 30
```
</details>

---

