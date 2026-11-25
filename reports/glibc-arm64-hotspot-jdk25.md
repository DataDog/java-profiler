---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795610790 33
1795610795 33
1795610800 33
1795610805 33
1795610810 33
1795610815 33
1795610820 33
1795610825 33
1795610830 33
1795610835 33
1795610840 33
1795610845 33
1795610850 33
1795610855 33
1795610860 33
1795610865 33
1795610870 33
1795610875 33
1795610880 33
1795610885 33
```
</details>

---

