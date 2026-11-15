---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:26:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794784907 43
1794784912 43
1794784917 43
1794784922 43
1794784927 43
1794784932 43
1794784937 43
1794784942 43
1794784947 43
1794784952 43
1794784957 43
1794784962 43
1794784967 48
1794784972 48
1794784977 48
1794784982 48
1794784987 48
1794784992 48
1794784997 48
1794785002 48
```
</details>

---

