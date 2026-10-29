---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 11:53:29 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 38-40 cores)</summary>

```
1793288630 39
1793288635 39
1793288640 39
1793288645 40
1793288650 40
1793288655 40
1793288660 40
1793288665 40
1793288670 40
1793288675 40
1793288680 40
1793288685 38
1793288690 38
1793288695 38
1793288700 38
1793288705 38
1793288710 38
1793288715 38
1793288720 38
1793288725 38
```
</details>

---

