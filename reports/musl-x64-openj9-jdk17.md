---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-03 09:41:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 90-96 cores)</summary>

```
1788442496 91
1788442501 91
1788442506 91
1788442511 96
1788442516 96
1788442521 94
1788442526 94
1788442531 94
1788442536 94
1788442541 90
1788442546 90
1788442551 90
1788442556 90
1788442561 90
1788442566 90
1788442571 90
1788442576 92
1788442581 92
1788442586 92
1788442591 90
```
</details>

---

