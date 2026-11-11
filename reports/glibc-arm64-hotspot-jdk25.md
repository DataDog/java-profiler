---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:02:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794405472 48
1794405477 36
1794405482 36
1794405487 36
1794405492 36
1794405497 36
1794405502 36
1794405507 36
1794405512 36
1794405518 36
1794405523 36
1794405528 36
1794405533 36
1794405538 36
1794405543 36
1794405548 36
1794405553 36
1794405558 36
1794405563 36
1794405568 36
```
</details>

---

