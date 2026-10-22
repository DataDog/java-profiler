---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 01:13:28 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 12 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792645591 43
1792645596 43
1792645601 43
1792645606 43
1792645611 43
1792645616 43
1792645621 43
1792645626 43
1792645631 43
1792645636 48
1792645641 48
1792645646 48
1792645651 48
1792645656 48
1792645661 48
1792645666 48
1792645671 48
1792645676 48
1792645681 48
1792645686 48
```
</details>

---

