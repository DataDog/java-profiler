---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 15:28:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1787080921 91
1787080926 91
1787080931 91
1787080936 91
1787080941 91
1787080946 91
1787080951 91
1787080956 91
1787080961 91
1787080966 96
1787080971 96
1787080976 96
1787080981 96
1787080986 96
1787080991 96
1787080996 96
1787081001 96
1787081006 96
1787081011 94
1787081016 94
```
</details>

---

