---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793734749 30
1793734754 30
1793734759 30
1793734764 30
1793734769 30
1793734774 30
1793734779 30
1793734784 30
1793734789 30
1793734794 30
1793734799 30
1793734804 30
1793734809 30
1793734814 30
1793734819 30
1793734824 30
1793734829 30
1793734834 30
1793734839 30
1793734844 30
```
</details>

---

