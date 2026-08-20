---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 10:46:54 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (4 unique values: 17-22 cores)</summary>

```
1787236920 17
1787236925 17
1787236930 21
1787236935 21
1787236940 21
1787236945 21
1787236950 21
1787236955 21
1787236960 22
1787236965 22
1787236970 22
1787236975 22
1787236980 22
1787236985 22
1787236990 22
1787236995 22
1787237000 22
1787237005 22
1787237010 22
1787237015 22
```
</details>

---

