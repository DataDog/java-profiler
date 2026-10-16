---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-16 06:16:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1792145497 25
1792145502 25
1792145507 25
1792145512 25
1792145517 25
1792145522 25
1792145527 25
1792145532 25
1792145537 25
1792145542 25
1792145547 25
1792145552 27
1792145557 27
1792145562 27
1792145567 27
1792145572 27
1792145577 27
1792145582 27
1792145587 27
1792145592 32
```
</details>

---

