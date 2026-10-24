---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:16:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1792833095 34
1792833100 34
1792833105 34
1792833110 24
1792833115 24
1792833120 24
1792833125 24
1792833130 24
1792833135 24
1792833140 24
1792833145 24
1792833150 29
1792833155 29
1792833160 29
1792833165 29
1792833170 29
1792833175 29
1792833180 29
1792833185 29
1792833190 29
```
</details>

---

