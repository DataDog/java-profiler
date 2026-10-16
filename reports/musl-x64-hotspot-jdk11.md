---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 11:26:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 53-63 cores)</summary>

```
1792163970 53
1792163975 53
1792163980 53
1792163985 53
1792163990 53
1792163995 53
1792164000 53
1792164005 53
1792164010 53
1792164015 53
1792164020 53
1792164025 53
1792164031 53
1792164036 61
1792164041 61
1792164046 61
1792164051 61
1792164056 61
1792164061 61
1792164066 61
```
</details>

---

