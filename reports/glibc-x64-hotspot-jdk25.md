---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 00:08:57 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 8 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 10-32 cores)</summary>

```
1794459770 32
1794459775 32
1794459780 32
1794459785 32
1794459790 32
1794459795 32
1794459800 32
1794459805 32
1794459810 32
1794459815 32
1794459820 32
1794459825 32
1794459830 32
1794459835 32
1794459840 32
1794459845 32
1794459850 32
1794459855 32
1794459860 32
1794459865 32
```
</details>

---

