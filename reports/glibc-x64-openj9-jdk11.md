---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 05:01:28 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (5 unique values: 25-50 cores)</summary>

```
1789721699 41
1789721704 41
1789721709 29
1789721714 29
1789721719 29
1789721724 29
1789721729 29
1789721734 29
1789721739 29
1789721744 29
1789721750 27
1789721755 27
1789721760 25
1789721765 25
1789721770 25
1789721775 25
1789721780 25
1789721785 25
1789721790 25
1789721795 25
```
</details>

---

