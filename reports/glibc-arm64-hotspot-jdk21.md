---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:37:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794832317 51
1794832322 51
1794832327 51
1794832332 51
1794832337 51
1794832342 51
1794832347 51
1794832352 51
1794832357 51
1794832362 51
1794832367 51
1794832372 51
1794832377 51
1794832382 51
1794832387 51
1794832392 46
1794832397 46
1794832402 46
1794832407 46
1794832412 46
```
</details>

---

