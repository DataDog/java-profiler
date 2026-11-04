---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 09:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793801565 64
1793801570 64
1793801575 64
1793801580 64
1793801585 62
1793801590 62
1793801595 62
1793801600 62
1793801605 62
1793801610 62
1793801615 62
1793801620 62
1793801625 62
1793801630 62
1793801635 62
1793801640 62
1793801645 62
1793801650 62
1793801655 62
1793801660 64
```
</details>

---

