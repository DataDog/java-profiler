---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 09:56:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 570 |

<details>
<summary>CPU Timeline (2 unique values: 53-62 cores)</summary>

```
1795618297 62
1795618302 62
1795618307 62
1795618312 53
1795618317 53
1795618322 53
1795618327 53
1795618332 53
1795618337 53
1795618342 53
1795618347 53
1795618352 53
1795618357 53
1795618362 53
1795618367 53
1795618372 53
1795618377 53
1795618382 53
1795618387 53
1795618392 53
```
</details>

---

