---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 14:30:59 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 9 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (5 unique values: 35-45 cores)</summary>

```
1794511565 45
1794511570 45
1794511575 45
1794511580 40
1794511585 40
1794511590 40
1794511595 40
1794511600 40
1794511605 40
1794511610 40
1794511615 40
1794511620 40
1794511625 40
1794511630 40
1794511635 40
1794511640 35
1794511645 35
1794511650 40
1794511655 40
1794511660 40
```
</details>

---

