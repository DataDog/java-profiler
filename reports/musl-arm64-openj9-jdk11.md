---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:01:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1795625808 33
1795625813 33
1795625818 33
1795625823 33
1795625828 33
1795625833 33
1795625838 33
1795625843 33
1795625848 33
1795625853 33
1795625858 33
1795625863 33
1795625868 33
1795625873 33
1795625878 33
1795625883 33
1795625888 33
1795625893 33
1795625898 33
1795625903 33
```
</details>

---

