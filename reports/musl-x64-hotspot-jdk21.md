---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:21:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794507317 79
1794507322 81
1794507327 81
1794507332 81
1794507337 81
1794507342 81
1794507347 81
1794507352 79
1794507358 79
1794507363 79
1794507368 79
1794507373 79
1794507378 79
1794507383 79
1794507388 79
1794507393 79
1794507398 79
1794507403 79
1794507408 79
1794507413 79
```
</details>

---

