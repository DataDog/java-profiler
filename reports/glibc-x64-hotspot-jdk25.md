---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 12:40:21 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (6 unique values: 70-80 cores)</summary>

```
1794418550 78
1794418555 78
1794418560 78
1794418565 80
1794418570 80
1794418575 80
1794418580 80
1794418585 79
1794418590 79
1794418595 79
1794418600 76
1794418605 76
1794418610 76
1794418615 76
1794418620 76
1794418625 76
1794418630 78
1794418635 78
1794418640 78
1794418645 70
```
</details>

---

