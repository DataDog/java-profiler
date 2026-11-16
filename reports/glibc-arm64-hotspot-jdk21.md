---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:37:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1794839632 45
1794839637 45
1794839642 45
1794839647 45
1794839652 45
1794839657 45
1794839662 47
1794839667 47
1794839672 48
1794839677 48
1794839682 48
1794839687 47
1794839692 47
1794839697 47
1794839702 47
1794839707 46
1794839712 46
1794839717 46
1794839722 46
1794839727 46
```
</details>

---

