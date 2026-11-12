---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:55:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794484086 31
1794484091 31
1794484096 31
1794484101 31
1794484106 31
1794484111 31
1794484116 31
1794484121 31
1794484126 31
1794484131 31
1794484136 31
1794484141 36
1794484146 36
1794484151 36
1794484156 36
1794484161 36
1794484166 36
1794484171 36
1794484176 36
1794484181 36
```
</details>

---

