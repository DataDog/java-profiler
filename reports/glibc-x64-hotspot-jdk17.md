---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 10:38:59 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 71-96 cores)</summary>

```
1789741910 96
1789741915 96
1789741920 96
1789741925 96
1789741930 96
1789741935 96
1789741940 96
1789741945 94
1789741950 94
1789741955 94
1789741960 94
1789741965 94
1789741970 94
1789741975 94
1789741980 94
1789741985 94
1789741990 94
1789741996 94
1789742001 71
1789742006 71
```
</details>

---

