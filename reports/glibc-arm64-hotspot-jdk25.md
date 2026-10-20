---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 12:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (4 unique values: 40-56 cores)</summary>

```
1792513498 53
1792513503 53
1792513508 53
1792513513 53
1792513518 53
1792513523 40
1792513528 40
1792513533 40
1792513538 40
1792513543 40
1792513548 40
1792513553 40
1792513558 40
1792513563 40
1792513568 40
1792513573 40
1792513578 40
1792513583 40
1792513588 40
1792513593 40
```
</details>

---

