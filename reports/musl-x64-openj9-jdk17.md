---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 01:04:10 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 13-30 cores)</summary>

```
1791349011 19
1791349016 19
1791349021 28
1791349026 28
1791349031 30
1791349036 30
1791349041 30
1791349046 30
1791349051 30
1791349056 30
1791349061 13
1791349066 13
1791349071 13
1791349076 13
1791349081 13
1791349086 13
1791349091 13
1791349096 13
1791349101 13
1791349106 13
```
</details>

---

