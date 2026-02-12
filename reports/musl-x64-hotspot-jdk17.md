---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-12 12:18:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 12 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 70-78 cores)</summary>

```
1770916312 70
1770916317 70
1770916322 70
1770916327 70
1770916332 70
1770916337 76
1770916342 76
1770916347 74
1770916352 74
1770916357 74
1770916362 74
1770916367 76
1770916372 76
1770916377 76
1770916382 76
1770916387 76
1770916392 78
1770916397 78
1770916402 78
1770916407 78
```
</details>

---

