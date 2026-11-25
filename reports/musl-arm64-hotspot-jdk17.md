---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:34:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 92 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1795613377 48
1795613382 48
1795613387 48
1795613392 48
1795613397 48
1795613402 48
1795613407 48
1795613412 48
1795613417 48
1795613422 48
1795613427 48
1795613432 48
1795613437 48
1795613442 48
1795613447 48
1795613452 46
1795613457 46
1795613462 46
1795613467 46
1795613472 46
```
</details>

---

