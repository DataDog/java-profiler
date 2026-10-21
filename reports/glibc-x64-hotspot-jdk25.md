---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-21 10:05:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 18-35 cores)</summary>

```
1792591253 20
1792591258 20
1792591263 18
1792591268 18
1792591273 18
1792591278 18
1792591283 18
1792591288 18
1792591293 18
1792591298 18
1792591303 35
1792591308 35
1792591313 35
1792591318 35
1792591323 35
1792591328 35
1792591333 35
1792591338 35
1792591343 35
1792591348 35
```
</details>

---

