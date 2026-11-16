---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:37:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 85-93 cores)</summary>

```
1794832292 85
1794832297 85
1794832302 85
1794832307 85
1794832312 85
1794832317 85
1794832322 85
1794832327 85
1794832332 85
1794832337 85
1794832342 85
1794832347 93
1794832352 93
1794832357 93
1794832362 93
1794832367 93
1794832372 93
1794832377 93
1794832382 93
1794832387 93
```
</details>

---

