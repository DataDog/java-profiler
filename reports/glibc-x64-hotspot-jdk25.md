---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:50:56 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1789731840 72
1789731845 72
1789731850 72
1789731855 72
1789731860 72
1789731865 72
1789731870 72
1789731875 72
1789731880 72
1789731885 72
1789731890 72
1789731895 70
1789731900 70
1789731905 70
1789731910 70
1789731915 70
1789731920 70
1789731925 70
1789731930 70
1789731935 70
```
</details>

---

