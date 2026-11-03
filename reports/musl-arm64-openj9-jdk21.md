---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 11 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793734724 14
1793734729 14
1793734734 14
1793734739 14
1793734744 14
1793734749 14
1793734754 9
1793734759 9
1793734764 9
1793734769 9
1793734774 9
1793734779 9
1793734784 9
1793734789 9
1793734794 14
1793734799 14
1793734804 14
1793734809 14
1793734814 14
1793734819 14
```
</details>

---

