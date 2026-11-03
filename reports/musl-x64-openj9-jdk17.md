---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 14:44:32 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1793734693 89
1793734698 89
1793734703 89
1793734708 89
1793734713 89
1793734718 89
1793734723 91
1793734728 91
1793734733 91
1793734738 91
1793734743 91
1793734748 93
1793734753 93
1793734759 93
1793734764 93
1793734769 93
1793734774 93
1793734779 93
1793734784 93
1793734789 93
```
</details>

---

