---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:35:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 15-56 cores)</summary>

```
1794396666 46
1794396671 46
1794396676 46
1794396681 46
1794396686 46
1794396691 46
1794396696 56
1794396701 56
1794396706 15
1794396711 15
1794396716 15
1794396721 15
1794396726 22
1794396731 22
1794396736 22
1794396741 22
1794396746 22
1794396751 22
1794396756 22
1794396761 22
```
</details>

---

