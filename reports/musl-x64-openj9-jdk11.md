---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:20:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 27-30 cores)</summary>

```
1790777815 29
1790777820 29
1790777825 29
1790777830 29
1790777835 29
1790777840 29
1790777845 29
1790777850 29
1790777855 29
1790777860 29
1790777865 27
1790777870 27
1790777875 27
1790777880 27
1790777885 27
1790777890 27
1790777895 27
1790777900 27
1790777905 30
1790777910 30
```
</details>

---

