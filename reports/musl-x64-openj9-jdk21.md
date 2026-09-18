---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 43-81 cores)</summary>

```
1789731801 81
1789731806 81
1789731811 81
1789731816 81
1789731821 81
1789731826 81
1789731831 81
1789731836 45
1789731841 45
1789731846 45
1789731851 45
1789731856 45
1789731861 45
1789731866 43
1789731871 43
1789731876 43
1789731881 43
1789731886 43
1789731891 43
1789731896 45
```
</details>

---

