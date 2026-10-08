---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1791470911 43
1791470916 43
1791470921 43
1791470926 43
1791470931 43
1791470936 43
1791470942 43
1791470947 43
1791470952 48
1791470957 48
1791470962 43
1791470967 43
1791470972 43
1791470977 43
1791470982 43
1791470987 43
1791470992 43
1791470997 43
1791471002 43
1791471007 43
```
</details>

---

