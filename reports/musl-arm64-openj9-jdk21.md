---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 09:58:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 41-51 cores)</summary>

```
1791986010 41
1791986015 51
1791986020 51
1791986025 51
1791986030 51
1791986036 51
1791986041 51
1791986046 51
1791986051 51
1791986056 51
1791986061 51
1791986066 51
1791986071 51
1791986076 51
1791986081 51
1791986086 51
1791986091 51
1791986096 51
1791986101 51
1791986106 51
```
</details>

---

