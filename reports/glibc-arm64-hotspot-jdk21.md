---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 06:11:47 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 42-46 cores)</summary>

```
1792490746 42
1792490751 42
1792490756 42
1792490761 42
1792490766 43
1792490771 43
1792490776 46
1792490781 46
1792490786 46
1792490791 46
1792490796 46
1792490801 46
1792490806 46
1792490811 46
1792490816 46
1792490821 46
1792490826 46
1792490831 46
1792490836 46
1792490841 46
```
</details>

---

