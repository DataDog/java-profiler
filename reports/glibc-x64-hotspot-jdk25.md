---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 03:32:40 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 83-91 cores)</summary>

```
1793780936 91
1793780941 91
1793780946 91
1793780951 91
1793780956 91
1793780961 91
1793780966 91
1793780971 91
1793780976 91
1793780981 91
1793780986 91
1793780991 91
1793780996 91
1793781001 91
1793781006 91
1793781011 91
1793781016 91
1793781021 91
1793781026 91
1793781031 91
```
</details>

---

