---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 17:43:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1790026699 23
1790026704 23
1790026709 23
1790026714 23
1790026719 23
1790026724 23
1790026729 23
1790026734 23
1790026739 23
1790026744 23
1790026749 23
1790026754 23
1790026759 23
1790026764 23
1790026769 23
1790026774 23
1790026779 23
1790026784 23
1790026789 32
1790026794 32
```
</details>

---

