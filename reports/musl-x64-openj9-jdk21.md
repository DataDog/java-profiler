---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 13:59:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1795200871 48
1795200876 48
1795200881 48
1795200886 46
1795200891 46
1795200896 46
1795200901 46
1795200906 46
1795200911 46
1795200916 46
1795200921 46
1795200926 46
1795200931 46
1795200936 46
1795200941 46
1795200946 38
1795200951 38
1795200956 38
1795200961 38
1795200966 38
```
</details>

---

