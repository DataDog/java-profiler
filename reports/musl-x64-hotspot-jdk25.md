---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:37:18 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 76-84 cores)</summary>

```
1794832292 84
1794832297 84
1794832302 84
1794832307 84
1794832312 84
1794832317 84
1794832322 84
1794832327 84
1794832332 84
1794832337 84
1794832342 84
1794832347 84
1794832352 84
1794832357 84
1794832362 76
1794832367 76
1794832372 76
1794832377 76
1794832382 76
1794832387 76
```
</details>

---

