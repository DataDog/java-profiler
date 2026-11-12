---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:57:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794498725 43
1794498730 43
1794498735 48
1794498740 48
1794498745 48
1794498750 48
1794498755 48
1794498760 48
1794498765 48
1794498770 48
1794498775 48
1794498780 48
1794498785 48
1794498790 48
1794498795 48
1794498800 48
1794498805 48
1794498810 48
1794498815 48
1794498820 48
```
</details>

---

