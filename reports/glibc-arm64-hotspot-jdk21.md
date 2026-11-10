---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 08:56:38 EST

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794318725 48
1794318730 48
1794318735 48
1794318740 48
1794318745 48
1794318750 48
1794318755 48
1794318760 48
1794318765 48
1794318770 48
1794318775 48
1794318780 48
1794318785 48
1794318790 48
1794318795 48
1794318800 48
1794318805 48
1794318810 48
1794318815 44
1794318820 44
```
</details>

---

