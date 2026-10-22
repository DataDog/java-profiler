---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 06:46:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1792665776 29
1792665781 29
1792665786 29
1792665791 29
1792665796 29
1792665801 29
1792665806 29
1792665811 29
1792665816 29
1792665821 29
1792665826 29
1792665831 29
1792665836 29
1792665841 32
1792665846 32
1792665851 32
1792665856 32
1792665861 32
1792665866 32
1792665871 32
```
</details>

---

