---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:36:30 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 56-75 cores)</summary>

```
1794407499 75
1794407504 75
1794407509 75
1794407514 75
1794407519 75
1794407524 75
1794407529 75
1794407534 75
1794407539 75
1794407544 75
1794407549 75
1794407554 75
1794407559 75
1794407564 75
1794407569 75
1794407574 65
1794407579 65
1794407584 65
1794407589 65
1794407594 56
```
</details>

---

