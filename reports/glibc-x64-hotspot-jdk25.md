---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 09:08:01 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1773234084 32
1773234089 32
1773234094 32
1773234099 32
1773234104 32
1773234109 32
1773234114 32
1773234119 32
1773234124 32
1773234129 32
1773234134 32
1773234139 32
1773234144 32
1773234149 32
1773234154 32
1773234159 32
1773234164 32
1773234169 32
1773234174 32
1773234179 32
```
</details>

---

