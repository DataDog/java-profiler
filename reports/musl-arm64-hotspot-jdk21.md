---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 07:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 11 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1790855136 48
1790855141 48
1790855146 48
1790855151 48
1790855156 48
1790855161 48
1790855166 48
1790855171 48
1790855176 48
1790855181 48
1790855186 48
1790855191 48
1790855196 48
1790855201 53
1790855206 53
1790855211 53
1790855216 53
1790855221 53
1790855226 53
1790855231 53
```
</details>

---

