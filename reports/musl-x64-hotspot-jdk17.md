---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 15:37:34 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 995 |
| Sample Rate | 16.58/sec |
| Health Score | 1036% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 60-96 cores)</summary>

```
1789673432 87
1789673437 87
1789673442 87
1789673447 89
1789673452 89
1789673457 89
1789673462 89
1789673467 89
1789673472 89
1789673477 89
1789673482 96
1789673487 96
1789673492 96
1789673497 96
1789673502 60
1789673507 60
1789673512 60
1789673517 60
1789673522 60
1789673527 60
```
</details>

---

