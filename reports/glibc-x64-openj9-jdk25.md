---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 08:20:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 63-71 cores)</summary>

```
1794402911 69
1794402916 69
1794402921 69
1794402926 71
1794402931 71
1794402936 69
1794402941 69
1794402946 69
1794402951 67
1794402956 67
1794402961 67
1794402966 67
1794402971 69
1794402976 69
1794402981 69
1794402986 67
1794402991 67
1794402996 65
1794403001 65
1794403006 63
```
</details>

---

