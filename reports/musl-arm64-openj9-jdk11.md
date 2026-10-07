---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 08:18:43 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 17-39 cores)</summary>

```
1791375250 17
1791375255 17
1791375260 17
1791375265 17
1791375270 17
1791375275 17
1791375280 17
1791375285 17
1791375290 17
1791375296 17
1791375301 17
1791375306 28
1791375311 28
1791375316 39
1791375321 39
1791375326 39
1791375331 39
1791375336 39
1791375341 39
1791375346 39
```
</details>

---

