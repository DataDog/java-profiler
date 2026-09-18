---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:50:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1789731850 27
1789731855 27
1789731860 27
1789731865 27
1789731870 27
1789731875 27
1789731880 27
1789731885 27
1789731890 27
1789731895 27
1789731900 27
1789731905 27
1789731910 30
1789731915 30
1789731920 30
1789731925 30
1789731931 30
1789731936 30
1789731941 30
1789731946 30
```
</details>

---

