---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790168720 40
1790168725 40
1790168730 45
1790168735 45
1790168740 45
1790168745 45
1790168750 45
1790168755 45
1790168760 45
1790168765 45
1790168770 45
1790168775 45
1790168780 45
1790168785 45
1790168790 45
1790168795 45
1790168800 45
1790168805 45
1790168810 45
1790168815 45
```
</details>

---

