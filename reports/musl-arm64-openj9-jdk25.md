---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-14 10:14:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 19-26 cores)</summary>

```
1786716529 24
1786716534 24
1786716539 24
1786716544 24
1786716549 24
1786716554 24
1786716559 24
1786716564 24
1786716569 24
1786716574 24
1786716579 24
1786716584 24
1786716589 24
1786716594 26
1786716599 26
1786716604 26
1786716609 26
1786716614 26
1786716619 26
1786716624 26
```
</details>

---

