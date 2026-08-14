---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-14 10:14:45 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 8 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1786716546 34
1786716551 34
1786716556 34
1786716561 34
1786716566 34
1786716571 34
1786716576 34
1786716581 34
1786716586 34
1786716591 34
1786716596 34
1786716601 34
1786716606 34
1786716611 34
1786716616 34
1786716621 29
1786716626 29
1786716631 29
1786716636 29
1786716641 29
```
</details>

---

