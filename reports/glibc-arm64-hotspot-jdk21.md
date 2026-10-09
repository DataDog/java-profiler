---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 12:44:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1791563925 48
1791563930 36
1791563935 36
1791563940 36
1791563945 36
1791563950 36
1791563955 36
1791563960 36
1791563965 36
1791563970 36
1791563975 36
1791563980 36
1791563985 36
1791563990 36
1791563995 36
1791564000 36
1791564005 36
1791564010 36
1791564015 36
1791564020 36
```
</details>

---

