---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-06 14:10:47 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 82-87 cores)</summary>

```
1778090741 85
1778090746 85
1778090751 85
1778090756 85
1778090761 85
1778090766 87
1778090771 87
1778090776 87
1778090781 87
1778090786 87
1778090791 87
1778090796 87
1778090801 87
1778090806 87
1778090811 87
1778090816 87
1778090821 83
1778090826 83
1778090831 83
1778090836 83
```
</details>

---

