---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:37:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 36-40 cores)</summary>

```
1794839600 36
1794839606 36
1794839611 38
1794839616 38
1794839621 38
1794839626 38
1794839631 38
1794839636 38
1794839641 38
1794839646 38
1794839651 38
1794839656 38
1794839661 38
1794839666 38
1794839671 38
1794839676 38
1794839681 38
1794839686 38
1794839691 38
1794839696 38
```
</details>

---

