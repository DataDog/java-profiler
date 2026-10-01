---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:23:43 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 19-50 cores)</summary>

```
1790853537 19
1790853542 19
1790853547 19
1790853552 19
1790853557 19
1790853562 19
1790853567 21
1790853572 21
1790853577 21
1790853582 21
1790853587 21
1790853592 21
1790853597 21
1790853602 21
1790853607 21
1790853612 21
1790853617 21
1790853622 21
1790853627 19
1790853632 19
```
</details>

---

