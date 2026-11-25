---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:36:21 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (5 unique values: 81-92 cores)</summary>

```
1795631439 92
1795631444 92
1795631449 86
1795631454 86
1795631459 86
1795631465 86
1795631470 88
1795631475 88
1795631480 90
1795631485 90
1795631490 90
1795631495 81
1795631500 81
1795631505 81
1795631510 81
1795631515 81
1795631520 81
1795631525 81
1795631530 81
1795631535 81
```
</details>

---

