---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-27 10:49:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1787841913 59
1787841918 59
1787841923 59
1787841928 59
1787841933 59
1787841938 59
1787841943 59
1787841948 59
1787841953 54
1787841958 54
1787841963 54
1787841968 54
1787841974 54
1787841979 54
1787841984 54
1787841989 54
1787841994 54
1787841999 54
1787842004 54
1787842009 54
```
</details>

---

