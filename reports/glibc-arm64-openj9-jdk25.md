---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:41:16 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793633830 39
1793633835 39
1793633840 39
1793633845 39
1793633850 39
1793633855 34
1793633860 34
1793633865 34
1793633870 34
1793633875 34
1793633880 34
1793633885 34
1793633890 34
1793633895 34
1793633900 34
1793633905 34
1793633910 34
1793633915 34
1793633920 34
1793633925 39
```
</details>

---

