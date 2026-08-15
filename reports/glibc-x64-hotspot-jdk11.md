---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-15 05:47:12 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 30-81 cores)</summary>

```
1786786983 30
1786786988 30
1786786993 30
1786786998 30
1786787003 30
1786787008 30
1786787013 30
1786787018 30
1786787023 30
1786787028 30
1786787033 30
1786787038 30
1786787043 81
1786787048 81
1786787053 81
1786787058 81
1786787063 81
1786787068 81
1786787073 81
1786787078 81
```
</details>

---

