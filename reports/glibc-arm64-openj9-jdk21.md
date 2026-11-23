---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:42:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795426756 29
1795426761 29
1795426766 29
1795426771 29
1795426776 29
1795426781 29
1795426786 29
1795426791 29
1795426796 29
1795426801 29
1795426806 34
1795426811 34
1795426816 34
1795426821 34
1795426826 34
1795426831 34
1795426836 34
1795426841 34
1795426846 34
1795426851 34
```
</details>

---

