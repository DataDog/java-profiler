---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-10 17:36:42 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 13 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 75-85 cores)</summary>

```
1770762535 85
1770762540 85
1770762545 85
1770762550 85
1770762555 85
1770762560 85
1770762565 85
1770762570 83
1770762576 83
1770762581 83
1770762586 83
1770762591 83
1770762596 75
1770762601 75
1770762606 75
1770762611 77
1770762616 77
1770762621 77
1770762626 77
1770762631 77
```
</details>

---

