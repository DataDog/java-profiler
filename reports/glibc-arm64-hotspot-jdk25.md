---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 07:03:14 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1790247581 48
1790247586 48
1790247591 48
1790247596 48
1790247601 48
1790247606 48
1790247611 48
1790247616 48
1790247621 48
1790247626 48
1790247631 48
1790247636 48
1790247641 48
1790247646 48
1790247651 48
1790247656 48
1790247661 48
1790247666 48
1790247671 48
1790247676 47
```
</details>

---

