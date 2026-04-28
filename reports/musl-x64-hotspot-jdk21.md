---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 10:04:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (7 unique values: 60-91 cores)</summary>

```
1777384892 91
1777384897 91
1777384902 85
1777384907 85
1777384912 85
1777384917 85
1777384922 83
1777384927 83
1777384932 83
1777384937 81
1777384942 81
1777384947 81
1777384952 81
1777384957 81
1777384962 81
1777384967 81
1777384972 85
1777384977 85
1777384982 80
1777384987 80
```
</details>

---

