---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794792323 64
1794792328 64
1794792333 64
1794792338 64
1794792343 64
1794792348 64
1794792353 64
1794792358 64
1794792363 64
1794792368 64
1794792373 64
1794792378 64
1794792383 64
1794792388 64
1794792393 64
1794792398 64
1794792403 64
1794792408 64
1794792413 64
1794792418 64
```
</details>

---

