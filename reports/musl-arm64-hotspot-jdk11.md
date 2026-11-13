---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 19:03:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 21-26 cores)</summary>

```
1794527947 21
1794527952 21
1794527957 21
1794527962 21
1794527967 21
1794527972 26
1794527977 26
1794527982 26
1794527987 26
1794527992 26
1794527997 26
1794528002 26
1794528007 26
1794528012 26
1794528017 26
1794528022 26
1794528027 26
1794528032 22
1794528037 22
1794528042 22
```
</details>

---

