---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:24:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1794431662 82
1794431667 82
1794431672 82
1794431677 82
1794431682 82
1794431687 82
1794431692 82
1794431697 85
1794431702 85
1794431707 94
1794431712 94
1794431717 94
1794431722 94
1794431727 94
1794431732 94
1794431737 94
1794431742 94
1794431747 94
1794431752 94
1794431757 94
```
</details>

---

