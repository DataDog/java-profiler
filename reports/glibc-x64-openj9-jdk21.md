---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 12 |
| Allocations | 412 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793734769 94
1793734774 94
1793734779 94
1793734784 94
1793734789 94
1793734794 94
1793734799 94
1793734804 94
1793734809 94
1793734814 94
1793734819 94
1793734824 94
1793734829 94
1793734834 94
1793734839 94
1793734844 96
1793734849 96
1793734854 96
1793734859 96
1793734864 96
```
</details>

---

