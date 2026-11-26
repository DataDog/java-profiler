---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:18:51 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 78-81 cores)</summary>

```
1795705975 81
1795705980 81
1795705985 81
1795705990 81
1795705995 81
1795706000 81
1795706005 81
1795706010 81
1795706015 81
1795706020 81
1795706025 81
1795706030 81
1795706035 81
1795706040 81
1795706046 81
1795706051 81
1795706056 81
1795706061 81
1795706066 81
1795706071 81
```
</details>

---

