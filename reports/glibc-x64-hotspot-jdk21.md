---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 09:08:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 18-32 cores)</summary>

```
1773234094 28
1773234099 30
1773234104 30
1773234109 30
1773234114 30
1773234119 30
1773234124 30
1773234129 30
1773234134 32
1773234139 32
1773234144 28
1773234149 28
1773234154 28
1773234159 28
1773234164 28
1773234169 28
1773234174 28
1773234179 28
1773234184 28
1773234189 28
```
</details>

---

