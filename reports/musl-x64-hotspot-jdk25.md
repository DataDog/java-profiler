---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 44-96 cores)</summary>

```
1790238269 44
1790238274 44
1790238279 61
1790238284 61
1790238289 61
1790238294 61
1790238299 61
1790238304 61
1790238309 61
1790238314 61
1790238319 61
1790238324 61
1790238329 61
1790238334 61
1790238339 61
1790238344 84
1790238349 84
1790238354 84
1790238359 84
1790238364 96
```
</details>

---

