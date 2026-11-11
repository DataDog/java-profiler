---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 16:04:56 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 59-69 cores)</summary>

```
1794430772 69
1794430777 69
1794430782 69
1794430787 69
1794430792 63
1794430797 63
1794430802 63
1794430807 63
1794430812 59
1794430817 59
1794430822 59
1794430827 59
1794430832 59
1794430837 59
1794430842 59
1794430847 59
1794430852 59
1794430857 59
1794430862 59
1794430867 59
```
</details>

---

