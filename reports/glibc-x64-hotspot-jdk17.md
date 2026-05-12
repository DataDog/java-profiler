---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 02:56:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 41-44 cores)</summary>

```
1778568816 43
1778568821 43
1778568826 43
1778568831 43
1778568836 43
1778568841 43
1778568846 43
1778568851 43
1778568856 43
1778568861 43
1778568866 43
1778568871 43
1778568876 43
1778568881 43
1778568886 41
1778568891 41
1778568896 41
1778568901 41
1778568906 42
1778568911 42
```
</details>

---

