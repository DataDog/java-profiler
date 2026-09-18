---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 314 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 56-61 cores)</summary>

```
1789731987 59
1789731992 59
1789731997 59
1789732002 59
1789732007 59
1789732012 59
1789732017 59
1789732022 59
1789732027 61
1789732032 61
1789732037 57
1789732042 57
1789732047 57
1789732052 57
1789732057 57
1789732062 57
1789732067 57
1789732072 57
1789732077 57
1789732082 57
```
</details>

---

