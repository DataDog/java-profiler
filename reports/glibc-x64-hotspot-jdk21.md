---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:38:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 61-64 cores)</summary>

```
1790238830 63
1790238835 63
1790238840 63
1790238845 61
1790238850 61
1790238855 61
1790238860 61
1790238865 62
1790238870 62
1790238875 62
1790238880 62
1790238885 62
1790238890 64
1790238895 64
1790238900 64
1790238905 64
1790238910 64
1790238915 64
1790238920 64
1790238925 64
```
</details>

---

