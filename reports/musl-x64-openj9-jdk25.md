---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:33:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 72-75 cores)</summary>

```
1794932957 72
1794932962 72
1794932967 72
1794932972 72
1794932977 72
1794932982 72
1794932987 72
1794932992 72
1794932997 72
1794933002 72
1794933007 72
1794933012 72
1794933017 72
1794933022 75
1794933027 75
1794933032 75
1794933037 75
1794933042 75
1794933047 75
1794933052 75
```
</details>

---

