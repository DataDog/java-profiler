---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 08:46:04 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786538503 48
1786538508 48
1786538513 48
1786538518 48
1786538523 48
1786538528 48
1786538533 48
1786538538 48
1786538543 48
1786538548 48
1786538553 48
1786538558 48
1786538563 48
1786538568 44
1786538573 44
1786538578 44
1786538583 44
1786538588 44
1786538593 44
1786538598 48
```
</details>

---

