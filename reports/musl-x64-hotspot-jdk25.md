---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:34:19 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 11 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (3 unique values: 65-87 cores)</summary>

```
1795613377 87
1795613382 87
1795613387 87
1795613392 87
1795613397 87
1795613402 87
1795613407 87
1795613412 87
1795613417 87
1795613422 87
1795613427 87
1795613432 87
1795613437 87
1795613442 87
1795613447 85
1795613452 85
1795613457 85
1795613462 85
1795613467 85
1795613472 85
```
</details>

---

