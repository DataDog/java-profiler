---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-09 05:44:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1791538776 86
1791538781 86
1791538786 86
1791538791 86
1791538796 84
1791538801 84
1791538806 84
1791538811 84
1791538816 84
1791538821 84
1791538826 84
1791538831 84
1791538836 86
1791538841 86
1791538846 86
1791538851 86
1791538856 86
1791538861 86
1791538866 86
1791538871 86
```
</details>

---

