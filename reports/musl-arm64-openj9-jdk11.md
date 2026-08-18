---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 08:24:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 14 |
| Allocations | 197 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1787055564 48
1787055569 48
1787055574 48
1787055579 48
1787055584 48
1787055589 48
1787055594 48
1787055599 48
1787055604 48
1787055609 48
1787055614 36
1787055619 36
1787055624 36
1787055629 36
1787055634 36
1787055639 36
1787055644 36
1787055649 36
1787055654 36
1787055659 36
```
</details>

---

