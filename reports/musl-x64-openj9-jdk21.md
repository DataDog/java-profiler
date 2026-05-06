---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:42:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 42-62 cores)</summary>

```
1778092689 42
1778092694 42
1778092699 42
1778092704 62
1778092709 62
1778092714 62
1778092719 62
1778092724 62
1778092729 62
1778092734 62
1778092739 62
1778092744 62
1778092749 62
1778092754 62
1778092759 62
1778092764 62
1778092770 62
1778092775 62
1778092780 62
1778092785 62
```
</details>

---

