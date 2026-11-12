---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:08:07 EST

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
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 78-84 cores)</summary>

```
1794506565 78
1794506570 78
1794506575 78
1794506580 78
1794506585 84
1794506590 84
1794506595 84
1794506600 84
1794506605 84
1794506610 84
1794506615 84
1794506620 84
1794506625 84
1794506630 84
1794506635 79
1794506640 79
1794506645 79
1794506650 79
1794506655 79
1794506660 79
```
</details>

---

