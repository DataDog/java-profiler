---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:28:40 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795796642 85
1795796647 85
1795796652 85
1795796657 85
1795796662 85
1795796667 85
1795796672 85
1795796677 85
1795796682 85
1795796687 85
1795796692 85
1795796697 85
1795796702 83
1795796707 83
1795796712 83
1795796717 83
1795796722 83
1795796727 83
1795796732 83
1795796737 83
```
</details>

---

