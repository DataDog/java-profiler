---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 09:56:51 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1770389495 96
1770389500 96
1770389505 96
1770389510 96
1770389515 96
1770389520 96
1770389525 96
1770389530 96
1770389535 96
1770389540 86
1770389545 86
1770389550 86
1770389555 86
1770389560 86
1770389565 86
1770389570 86
1770389575 86
1770389580 86
1770389585 86
1770389590 86
```
</details>

---

