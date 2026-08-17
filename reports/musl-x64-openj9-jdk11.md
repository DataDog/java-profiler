---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 14:10:27 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 58-66 cores)</summary>

```
1786989931 66
1786989936 66
1786989941 66
1786989946 66
1786989951 66
1786989956 66
1786989961 66
1786989966 66
1786989971 66
1786989976 66
1786989981 66
1786989986 66
1786989991 66
1786989996 66
1786990001 66
1786990006 66
1786990011 66
1786990016 66
1786990021 66
1786990026 66
```
</details>

---

