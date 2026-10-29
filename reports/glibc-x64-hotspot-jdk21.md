---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 13:49:34 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 12 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 75-78 cores)</summary>

```
1793295826 78
1793295831 78
1793295836 78
1793295841 78
1793295846 78
1793295851 78
1793295856 78
1793295861 78
1793295866 78
1793295871 78
1793295876 75
1793295881 75
1793295886 75
1793295891 78
1793295896 78
1793295901 78
1793295906 78
1793295911 78
1793295916 78
1793295921 78
```
</details>

---

