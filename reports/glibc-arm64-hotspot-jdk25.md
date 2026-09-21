---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 03:29:10 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 10 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1789975478 46
1789975483 46
1789975488 46
1789975493 46
1789975498 46
1789975503 46
1789975508 46
1789975513 46
1789975518 46
1789975523 45
1789975528 45
1789975533 45
1789975538 45
1789975543 45
1789975548 45
1789975553 48
1789975558 48
1789975563 48
1789975568 48
1789975573 48
```
</details>

---

