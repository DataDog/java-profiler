---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 18:13:26 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 23-25 cores)</summary>

```
1777413973 25
1777413978 25
1777413983 25
1777413988 25
1777413993 25
1777413998 25
1777414003 25
1777414008 25
1777414013 23
1777414018 23
1777414023 23
1777414028 23
1777414033 23
1777414038 23
1777414043 23
1777414048 23
1777414053 23
1777414058 23
1777414063 23
1777414068 23
```
</details>

---

