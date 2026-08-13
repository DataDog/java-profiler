---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-13 00:57:14 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 42-47 cores)</summary>

```
1786596776 44
1786596781 44
1786596786 44
1786596791 44
1786596796 44
1786596801 44
1786596806 44
1786596811 44
1786596816 44
1786596821 44
1786596826 44
1786596831 44
1786596836 42
1786596841 42
1786596846 45
1786596851 45
1786596856 45
1786596861 45
1786596866 47
1786596871 47
```
</details>

---

