---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:15:31 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1794582650 83
1794582655 83
1794582660 83
1794582665 83
1794582670 83
1794582675 83
1794582680 83
1794582685 83
1794582690 83
1794582695 83
1794582700 83
1794582705 83
1794582710 83
1794582715 83
1794582720 83
1794582725 83
1794582730 83
1794582735 83
1794582740 83
1794582745 81
```
</details>

---

