---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 09:08:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 24-32 cores)</summary>

```
1773234089 24
1773234094 29
1773234099 29
1773234104 29
1773234109 29
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
1773234184 32
```
</details>

---

