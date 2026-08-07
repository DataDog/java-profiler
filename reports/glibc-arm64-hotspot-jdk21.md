---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 16:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 8 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 16-21 cores)</summary>

```
1786133290 19
1786133295 19
1786133300 19
1786133305 19
1786133310 19
1786133315 19
1786133320 19
1786133325 19
1786133330 19
1786133335 19
1786133340 19
1786133345 19
1786133350 19
1786133355 19
1786133360 19
1786133365 19
1786133370 21
1786133375 21
1786133380 21
1786133385 21
```
</details>

---

