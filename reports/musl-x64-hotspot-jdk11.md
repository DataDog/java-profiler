---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 10:58:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787064745 96
1787064750 96
1787064755 96
1787064760 96
1787064765 96
1787064770 96
1787064775 96
1787064780 96
1787064785 96
1787064790 96
1787064795 96
1787064800 96
1787064805 96
1787064810 96
1787064815 96
1787064820 96
1787064825 96
1787064830 96
1787064835 96
1787064840 88
```
</details>

---

