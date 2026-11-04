---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 03:32:41 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1793780917 48
1793780922 48
1793780927 53
1793780932 53
1793780937 53
1793780942 53
1793780947 53
1793780953 53
1793780958 53
1793780963 53
1793780968 53
1793780973 53
1793780978 48
1793780983 48
1793780988 48
1793780993 48
1793780998 48
1793781003 48
1793781008 48
1793781013 48
```
</details>

---

