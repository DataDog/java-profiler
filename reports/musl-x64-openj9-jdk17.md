---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:07:11 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1795618900 62
1795618905 62
1795618910 62
1795618915 62
1795618920 62
1795618925 62
1795618930 62
1795618935 60
1795618940 60
1795618945 60
1795618950 60
1795618955 60
1795618960 60
1795618965 58
1795618970 58
1795618975 58
1795618980 58
1795618985 58
1795618990 58
1795618995 58
```
</details>

---

