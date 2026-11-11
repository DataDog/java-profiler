---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:37:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 11 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794396763 43
1794396768 43
1794396773 43
1794396778 43
1794396783 43
1794396788 43
1794396793 38
1794396798 38
1794396803 38
1794396808 38
1794396813 38
1794396818 38
1794396823 38
1794396828 38
1794396833 38
1794396838 38
1794396843 38
1794396848 38
1794396853 38
1794396858 38
```
</details>

---

