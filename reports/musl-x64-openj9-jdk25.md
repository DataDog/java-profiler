---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 13:25:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 12 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 83-96 cores)</summary>

```
1787246443 96
1787246448 96
1787246453 96
1787246458 96
1787246463 96
1787246468 96
1787246473 96
1787246478 96
1787246483 96
1787246488 96
1787246493 96
1787246498 91
1787246503 91
1787246508 91
1787246513 91
1787246518 91
1787246523 91
1787246528 91
1787246533 83
1787246538 83
```
</details>

---

