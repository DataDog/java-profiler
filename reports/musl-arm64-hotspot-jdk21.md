---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 01:01:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 29-51 cores)</summary>

```
1786683297 29
1786683302 29
1786683307 29
1786683312 29
1786683317 29
1786683322 29
1786683327 29
1786683332 31
1786683337 31
1786683342 31
1786683347 31
1786683352 31
1786683357 31
1786683362 31
1786683367 31
1786683372 31
1786683377 31
1786683382 31
1786683387 31
1786683392 51
```
</details>

---

