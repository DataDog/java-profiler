---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 07:01:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 16.50/sec |
| Health Score | 1031% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 22.17/sec |
| Health Score | 1386% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (6 unique values: 28-67 cores)</summary>

```
1769687531 28
1769687536 28
1769687541 30
1769687546 30
1769687551 30
1769687556 67
1769687561 67
1769687566 31
1769687571 31
1769687576 31
1769687581 31
1769687586 31
1769687591 31
1769687596 31
1769687601 31
1769687606 36
1769687611 36
1769687616 36
1769687621 36
1769687626 36
```
</details>

---

