---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:42:33 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1778092690 51
1778092695 51
1778092700 51
1778092705 51
1778092710 51
1778092715 51
1778092720 51
1778092725 51
1778092730 51
1778092735 51
1778092740 51
1778092745 51
1778092750 51
1778092755 51
1778092760 51
1778092765 51
1778092770 51
1778092775 51
1778092781 51
1778092786 51
```
</details>

---

