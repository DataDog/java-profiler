---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 05:57:04 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 13 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (2 unique values: 6-16 cores)</summary>

```
1792749111 6
1792749116 16
1792749121 16
1792749126 16
1792749131 16
1792749136 16
1792749141 16
1792749146 16
1792749151 16
1792749156 16
1792749161 16
1792749166 16
1792749171 16
1792749176 16
1792749181 16
1792749186 16
1792749191 16
1792749196 16
1792749201 16
1792749206 16
```
</details>

---

