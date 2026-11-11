---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:36:30 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 11 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1794407497 23
1794407502 23
1794407507 23
1794407512 23
1794407517 23
1794407522 23
1794407527 23
1794407532 23
1794407537 23
1794407542 23
1794407547 23
1794407552 23
1794407557 23
1794407562 23
1794407567 23
1794407572 23
1794407577 23
1794407582 23
1794407587 28
1794407592 28
```
</details>

---

