---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1795618884 31
1795618889 31
1795618894 31
1795618899 31
1795618904 31
1795618909 31
1795618914 31
1795618920 31
1795618925 36
1795618930 36
1795618935 36
1795618940 36
1795618945 36
1795618950 36
1795618955 36
1795618960 36
1795618965 36
1795618970 36
1795618975 36
1795618980 36
```
</details>

---

