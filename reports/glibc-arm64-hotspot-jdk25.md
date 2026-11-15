---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:26:27 EST

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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794784964 48
1794784969 48
1794784974 48
1794784979 48
1794784984 48
1794784989 48
1794784994 48
1794785000 48
1794785005 48
1794785010 48
1794785015 48
1794785020 48
1794785025 48
1794785030 48
1794785035 48
1794785040 48
1794785045 48
1794785050 48
1794785055 48
1794785060 48
```
</details>

---

