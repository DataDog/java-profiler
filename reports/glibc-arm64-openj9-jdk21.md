---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 10:58:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (4 unique values: 19-29 cores)</summary>

```
1787064750 19
1787064755 19
1787064760 19
1787064765 19
1787064770 19
1787064775 19
1787064780 19
1787064785 19
1787064790 19
1787064795 24
1787064800 24
1787064805 24
1787064810 24
1787064815 29
1787064820 29
1787064825 29
1787064830 29
1787064835 29
1787064840 29
1787064845 26
```
</details>

---

