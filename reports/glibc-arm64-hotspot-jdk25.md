---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 03:38:43 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777275247 64
1777275252 64
1777275257 64
1777275262 64
1777275267 64
1777275272 64
1777275277 64
1777275282 64
1777275287 64
1777275292 64
1777275297 64
1777275302 64
1777275307 64
1777275312 64
1777275317 64
1777275322 64
1777275327 64
1777275332 64
1777275337 64
1777275342 64
```
</details>

---

