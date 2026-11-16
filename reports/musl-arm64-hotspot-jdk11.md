---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:29:54 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
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
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 13 |
| Allocations | 187 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1794792313 32
1794792318 32
1794792323 32
1794792328 32
1794792333 32
1794792338 34
1794792343 34
1794792348 34
1794792353 34
1794792358 34
1794792363 34
1794792368 34
1794792373 34
1794792378 34
1794792383 34
1794792388 34
1794792393 34
1794792398 34
1794792403 34
1794792408 34
```
</details>

---

