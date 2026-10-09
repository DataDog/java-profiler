---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 05:44:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1791538785 22
1791538790 24
1791538795 24
1791538800 24
1791538805 24
1791538810 24
1791538815 24
1791538820 24
1791538825 24
1791538830 24
1791538835 24
1791538840 24
1791538845 24
1791538850 24
1791538855 24
1791538860 32
1791538865 32
1791538870 32
1791538875 32
1791538880 32
```
</details>

---

