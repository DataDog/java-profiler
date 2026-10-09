---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-09 07:07:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 12-29 cores)</summary>

```
1791543828 12
1791543833 12
1791543838 12
1791543843 12
1791543848 12
1791543853 12
1791543858 12
1791543863 29
1791543868 29
1791543873 29
1791543878 29
1791543884 29
1791543889 29
1791543894 29
1791543899 29
1791543904 29
1791543909 29
1791543914 29
1791543919 29
1791543924 29
```
</details>

---

