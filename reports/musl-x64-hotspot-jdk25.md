---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 10:05:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 84-94 cores)</summary>

```
1787234495 94
1787234500 94
1787234505 94
1787234510 94
1787234515 94
1787234520 94
1787234525 94
1787234530 94
1787234535 94
1787234540 94
1787234545 94
1787234550 89
1787234555 89
1787234560 86
1787234565 86
1787234570 86
1787234575 86
1787234580 86
1787234585 86
1787234590 86
```
</details>

---

