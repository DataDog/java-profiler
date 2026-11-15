---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 08:15:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794748237 32
1794748242 32
1794748247 32
1794748252 32
1794748257 32
1794748262 32
1794748267 32
1794748272 32
1794748277 32
1794748282 32
1794748287 32
1794748292 32
1794748297 32
1794748302 32
1794748307 32
1794748312 32
1794748317 32
1794748322 32
1794748327 32
1794748332 32
```
</details>

---

