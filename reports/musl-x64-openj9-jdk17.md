---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:46:58 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 45-96 cores)</summary>

```
1795084956 96
1795084961 96
1795084966 96
1795084971 96
1795084976 96
1795084981 96
1795084986 77
1795084991 77
1795084996 77
1795085001 77
1795085006 77
1795085011 77
1795085016 77
1795085021 77
1795085026 77
1795085031 77
1795085036 77
1795085041 45
1795085046 45
1795085051 45
```
</details>

---

