---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:54:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 9 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791470936 43
1791470941 43
1791470946 43
1791470951 43
1791470956 43
1791470961 43
1791470966 43
1791470971 48
1791470976 48
1791470981 48
1791470986 43
1791470991 43
1791470996 43
1791471001 43
1791471006 43
1791471011 43
1791471016 43
1791471021 43
1791471026 43
1791471031 43
```
</details>

---

