---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:37:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 76-88 cores)</summary>

```
1794832282 86
1794832287 86
1794832292 86
1794832297 86
1794832302 86
1794832307 86
1794832312 86
1794832317 86
1794832322 86
1794832327 86
1794832332 86
1794832337 86
1794832342 86
1794832347 84
1794832352 84
1794832357 84
1794832362 84
1794832367 88
1794832372 88
1794832377 88
```
</details>

---

