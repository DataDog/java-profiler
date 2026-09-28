---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 9 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790604669 38
1790604674 38
1790604679 38
1790604684 38
1790604689 38
1790604694 38
1790604699 38
1790604704 38
1790604709 38
1790604714 38
1790604719 38
1790604724 38
1790604729 38
1790604734 38
1790604739 38
1790604744 38
1790604750 38
1790604755 38
1790604760 43
1790604765 43
```
</details>

---

