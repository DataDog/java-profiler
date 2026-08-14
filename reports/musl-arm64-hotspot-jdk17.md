---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-14 10:14:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 11 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 43-48 cores)</summary>

```
1786716513 43
1786716518 43
1786716523 48
1786716528 48
1786716533 48
1786716538 48
1786716543 48
1786716548 48
1786716553 47
1786716558 47
1786716563 47
1786716568 47
1786716573 47
1786716578 47
1786716583 46
1786716588 46
1786716593 46
1786716598 46
1786716603 46
1786716608 46
```
</details>

---

