---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 09:29:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 56-69 cores)</summary>

```
1792761948 67
1792761953 67
1792761958 69
1792761963 69
1792761968 69
1792761973 58
1792761978 58
1792761983 58
1792761988 60
1792761993 60
1792761998 58
1792762003 58
1792762008 58
1792762013 58
1792762018 58
1792762023 58
1792762028 58
1792762033 56
1792762038 56
1792762043 56
```
</details>

---

