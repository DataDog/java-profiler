---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 05:17:42 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1787130754 34
1787130759 34
1787130764 34
1787130769 34
1787130774 34
1787130779 34
1787130784 34
1787130789 34
1787130795 34
1787130800 31
1787130805 31
1787130810 31
1787130815 31
1787130820 31
1787130825 31
1787130830 31
1787130835 31
1787130840 31
1787130845 31
1787130850 34
```
</details>

---

