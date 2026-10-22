---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 13:10:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 35-43 cores)</summary>

```
1792688689 35
1792688694 35
1792688699 35
1792688704 35
1792688709 35
1792688714 35
1792688719 35
1792688724 35
1792688729 35
1792688734 35
1792688739 35
1792688744 35
1792688749 35
1792688754 35
1792688759 35
1792688764 35
1792688769 43
1792688774 43
1792688779 43
1792688784 43
```
</details>

---

