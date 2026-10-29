---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:49:34 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 89-94 cores)</summary>

```
1793295816 91
1793295821 91
1793295826 91
1793295831 91
1793295836 91
1793295841 91
1793295846 91
1793295851 91
1793295856 91
1793295861 91
1793295866 91
1793295871 91
1793295876 91
1793295881 89
1793295886 89
1793295891 89
1793295896 89
1793295901 89
1793295906 89
1793295911 89
```
</details>

---

