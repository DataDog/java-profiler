---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 33-36 cores)</summary>

```
1795803682 33
1795803687 36
1795803692 36
1795803697 36
1795803702 36
1795803707 36
1795803712 36
1795803717 36
1795803722 36
1795803727 36
1795803732 36
1795803737 36
1795803742 36
1795803747 36
1795803752 36
1795803757 36
1795803762 36
1795803767 36
1795803772 36
1795803777 36
```
</details>

---

