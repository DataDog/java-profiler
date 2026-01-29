---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 07:01:54 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 17.17/sec |
| Health Score | 1073% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 24.50/sec |
| Health Score | 1531% |
| Threads | 13 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 29-33 cores)</summary>

```
1769687517 33
1769687522 33
1769687527 33
1769687532 33
1769687537 33
1769687542 33
1769687547 33
1769687552 33
1769687557 33
1769687562 33
1769687567 33
1769687572 29
1769687577 29
1769687582 29
1769687587 29
1769687592 29
1769687597 29
1769687602 29
1769687607 29
1769687612 33
```
</details>

---

