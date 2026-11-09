---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:36:31 EST

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
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794238202 43
1794238207 43
1794238212 43
1794238217 43
1794238222 48
1794238227 48
1794238232 48
1794238237 48
1794238242 48
1794238247 48
1794238252 48
1794238257 48
1794238262 48
1794238267 48
1794238272 48
1794238277 48
1794238282 48
1794238287 48
1794238292 48
1794238297 48
```
</details>

---

