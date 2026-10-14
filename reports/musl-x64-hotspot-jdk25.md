---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 11:49:34 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 17-27 cores)</summary>

```
1791992497 17
1791992502 17
1791992507 17
1791992512 17
1791992517 17
1791992522 17
1791992527 17
1791992532 25
1791992537 25
1791992542 25
1791992547 25
1791992552 25
1791992557 25
1791992562 25
1791992567 25
1791992572 25
1791992577 25
1791992582 25
1791992587 25
1791992592 27
```
</details>

---

