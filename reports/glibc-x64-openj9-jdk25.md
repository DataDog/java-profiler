---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1790241547 61
1790241552 61
1790241557 61
1790241562 61
1790241567 61
1790241572 61
1790241577 61
1790241582 61
1790241587 61
1790241592 61
1790241597 61
1790241602 61
1790241607 61
1790241612 61
1790241617 61
1790241622 61
1790241627 61
1790241632 61
1790241637 61
1790241642 63
```
</details>

---

