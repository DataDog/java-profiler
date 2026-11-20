---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:01:32 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 38-50 cores)</summary>

```
1795168695 38
1795168700 38
1795168705 38
1795168710 38
1795168715 38
1795168720 38
1795168725 38
1795168730 38
1795168735 38
1795168740 38
1795168745 38
1795168750 38
1795168756 38
1795168761 38
1795168766 38
1795168771 38
1795168776 50
1795168781 50
1795168786 50
1795168791 50
```
</details>

---

