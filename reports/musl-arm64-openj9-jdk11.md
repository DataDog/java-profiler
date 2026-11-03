---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 7 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793734724 48
1793734729 48
1793734734 48
1793734739 48
1793734744 48
1793734749 48
1793734754 48
1793734759 48
1793734764 48
1793734769 48
1793734774 48
1793734779 48
1793734784 48
1793734789 48
1793734794 48
1793734799 48
1793734804 48
1793734809 48
1793734814 48
1793734819 48
```
</details>

---

