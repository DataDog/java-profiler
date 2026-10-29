---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 01:04:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1793249956 15
1793249961 15
1793249966 15
1793249971 15
1793249976 15
1793249981 15
1793249986 15
1793249992 15
1793249997 15
1793250002 15
1793250007 15
1793250012 15
1793250017 15
1793250022 15
1793250027 15
1793250032 15
1793250037 15
1793250042 15
1793250047 15
1793250052 15
```
</details>

---

