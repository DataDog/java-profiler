---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:39:53 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 47-68 cores)</summary>

```
1795451604 47
1795451610 47
1795451615 47
1795451620 56
1795451625 56
1795451630 56
1795451635 56
1795451640 56
1795451645 56
1795451650 56
1795451655 56
1795451660 56
1795451665 58
1795451670 58
1795451675 58
1795451680 58
1795451685 60
1795451690 60
1795451695 60
1795451700 60
```
</details>

---

