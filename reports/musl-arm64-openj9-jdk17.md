---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 12:11:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 20-38 cores)</summary>

```
1794243984 20
1794243989 20
1794243994 20
1794243999 20
1794244004 20
1794244009 20
1794244014 20
1794244019 20
1794244024 20
1794244029 20
1794244034 20
1794244039 20
1794244044 20
1794244049 20
1794244054 20
1794244059 20
1794244064 20
1794244069 25
1794244074 25
1794244079 25
```
</details>

---

