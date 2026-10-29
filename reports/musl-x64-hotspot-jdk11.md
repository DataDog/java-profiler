---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 08:13:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1045 |
| Sample Rate | 17.42/sec |
| Health Score | 1089% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1793275687 60
1793275692 60
1793275697 60
1793275702 60
1793275707 60
1793275712 60
1793275717 60
1793275722 60
1793275727 60
1793275733 62
1793275738 62
1793275743 60
1793275748 60
1793275753 60
1793275758 60
1793275763 60
1793275768 60
1793275773 60
1793275778 60
1793275783 60
```
</details>

---

