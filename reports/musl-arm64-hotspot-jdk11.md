---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 9 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 40-48 cores)</summary>

```
1794340088 48
1794340093 48
1794340098 48
1794340103 48
1794340108 48
1794340113 43
1794340118 43
1794340123 43
1794340128 43
1794340133 40
1794340138 40
1794340143 40
1794340148 40
1794340153 40
1794340158 40
1794340163 40
1794340168 40
1794340173 45
1794340178 45
1794340183 45
```
</details>

---

