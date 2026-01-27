---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 25.10/sec |
| Health Score | 1569% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 25.47/sec |
| Health Score | 1592% |
| Threads | 13 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1769524872 47
1769524877 47
1769524882 47
1769524887 47
1769524892 47
1769524897 47
1769524902 47
1769524907 47
1769524912 47
1769524917 47
1769524922 47
1769524927 47
1769524932 47
1769524937 47
1769524942 47
1769524947 47
1769524952 47
1769524957 47
1769524962 47
1769524967 51
```
</details>

---

