---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-09-02 09:15:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 73-81 cores)</summary>

```
1788354643 73
1788354648 73
1788354653 73
1788354658 73
1788354664 73
1788354669 73
1788354674 73
1788354679 73
1788354684 73
1788354689 73
1788354694 73
1788354699 73
1788354704 73
1788354709 73
1788354714 73
1788354719 73
1788354724 73
1788354729 79
1788354734 79
1788354739 79
```
</details>

---

