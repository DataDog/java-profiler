---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 10:50:54 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795189652 50
1795189657 50
1795189662 50
1795189667 64
1795189672 64
1795189677 64
1795189682 64
1795189687 64
1795189692 64
1795189697 64
1795189702 64
1795189707 44
1795189712 44
1795189717 44
1795189722 44
1795189727 44
1795189732 44
1795189737 44
1795189742 44
1795189747 44
```
</details>

---

