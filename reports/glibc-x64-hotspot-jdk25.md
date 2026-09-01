---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-01 14:09:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788285851 94
1788285856 94
1788285861 94
1788285866 94
1788285871 94
1788285876 94
1788285881 94
1788285886 94
1788285891 94
1788285896 96
1788285901 96
1788285906 96
1788285911 96
1788285916 96
1788285921 96
1788285926 96
1788285931 96
1788285936 96
1788285941 96
1788285946 96
```
</details>

---

