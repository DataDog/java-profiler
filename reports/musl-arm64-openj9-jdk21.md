---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:37:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 14 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 39-43 cores)</summary>

```
1794832297 39
1794832302 39
1794832307 39
1794832312 39
1794832317 39
1794832322 39
1794832327 39
1794832332 39
1794832337 39
1794832342 39
1794832347 43
1794832352 43
1794832357 43
1794832362 43
1794832367 43
1794832372 43
1794832377 43
1794832382 43
1794832387 43
1794832392 43
```
</details>

---

