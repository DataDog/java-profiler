---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795529331 64
1795529336 64
1795529341 64
1795529346 64
1795529351 64
1795529356 64
1795529361 64
1795529366 64
1795529371 64
1795529376 64
1795529381 64
1795529386 64
1795529391 64
1795529396 64
1795529401 64
1795529406 64
1795529411 64
1795529416 60
1795529421 60
1795529427 60
```
</details>

---

