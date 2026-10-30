---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 06:56:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 10 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793357503 46
1793357508 46
1793357513 46
1793357518 48
1793357523 48
1793357528 48
1793357533 48
1793357538 43
1793357543 43
1793357548 43
1793357553 43
1793357558 43
1793357563 43
1793357568 43
1793357573 43
1793357578 43
1793357583 43
1793357588 43
1793357593 43
1793357598 43
```
</details>

---

