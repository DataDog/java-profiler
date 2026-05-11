---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:29:49 EDT

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
| CPU Cores (start) | 5 |
| CPU Cores (end) | 5 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 5-48 cores)</summary>

```
1778538094 5
1778538099 5
1778538104 5
1778538109 5
1778538114 48
1778538119 48
1778538124 48
1778538129 48
1778538134 48
1778538139 48
1778538144 48
1778538149 48
1778538154 48
1778538159 48
1778538164 48
1778538169 48
1778538174 5
1778538179 5
1778538184 5
1778538189 5
```
</details>

---

