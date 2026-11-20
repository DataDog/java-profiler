---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 16:44:19 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 63-84 cores)</summary>

```
1795210744 63
1795210749 63
1795210754 63
1795210759 63
1795210764 63
1795210769 63
1795210774 63
1795210779 63
1795210784 65
1795210789 65
1795210794 84
1795210799 84
1795210804 84
1795210809 84
1795210814 84
1795210819 84
1795210824 81
1795210829 81
1795210834 81
1795210839 81
```
</details>

---

