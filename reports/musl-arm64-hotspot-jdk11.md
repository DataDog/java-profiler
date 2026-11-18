---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:06:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795010560 46
1795010565 46
1795010570 46
1795010575 46
1795010580 46
1795010585 46
1795010590 46
1795010595 46
1795010600 46
1795010605 46
1795010610 46
1795010615 51
1795010620 51
1795010625 51
1795010630 51
1795010635 51
1795010640 51
1795010645 51
1795010650 51
1795010655 51
```
</details>

---

