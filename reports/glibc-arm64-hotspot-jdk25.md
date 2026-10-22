---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 06:46:58 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (7 unique values: 40-48 cores)</summary>

```
1792665788 44
1792665793 44
1792665798 47
1792665803 47
1792665808 48
1792665813 48
1792665818 47
1792665823 47
1792665828 47
1792665833 47
1792665838 47
1792665843 47
1792665848 47
1792665853 47
1792665858 45
1792665863 45
1792665868 45
1792665873 46
1792665878 46
1792665883 43
```
</details>

---

