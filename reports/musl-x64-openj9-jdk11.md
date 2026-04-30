---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 06:13:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1051 |
| Sample Rate | 17.52/sec |
| Health Score | 1095% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 52-72 cores)</summary>

```
1777543667 72
1777543672 72
1777543677 72
1777543682 72
1777543687 72
1777543692 72
1777543697 72
1777543702 72
1777543707 72
1777543712 72
1777543717 72
1777543722 68
1777543727 68
1777543732 68
1777543737 55
1777543742 55
1777543747 55
1777543752 55
1777543757 55
1777543762 55
```
</details>

---

