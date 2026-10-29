---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:32 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 13 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1793295840 48
1793295845 48
1793295850 48
1793295855 48
1793295860 48
1793295865 48
1793295870 48
1793295875 48
1793295880 48
1793295885 48
1793295890 47
1793295895 47
1793295900 47
1793295905 47
1793295910 47
1793295915 47
1793295920 47
1793295925 47
1793295930 47
1793295935 47
```
</details>

---

