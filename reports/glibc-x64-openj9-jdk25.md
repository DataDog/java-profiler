---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 14:00:46 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 12-15 cores)</summary>

```
1792518936 13
1792518941 13
1792518946 13
1792518951 13
1792518956 13
1792518961 13
1792518966 15
1792518971 15
1792518976 15
1792518981 15
1792518986 15
1792518991 15
1792518996 15
1792519001 15
1792519006 15
1792519011 15
1792519016 15
1792519021 12
1792519026 12
1792519031 12
```
</details>

---

