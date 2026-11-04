---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:17 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793800884 32
1793800889 32
1793800894 32
1793800899 32
1793800904 32
1793800909 32
1793800914 32
1793800919 32
1793800924 32
1793800929 32
1793800934 32
1793800939 32
1793800944 32
1793800949 32
1793800955 32
1793800960 32
1793800965 32
1793800970 32
1793800975 32
1793800980 32
```
</details>

---

