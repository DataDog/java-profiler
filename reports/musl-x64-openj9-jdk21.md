---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 08:33:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1791980913 30
1791980918 30
1791980923 30
1791980928 30
1791980933 30
1791980938 30
1791980943 30
1791980948 30
1791980953 30
1791980958 30
1791980963 30
1791980968 30
1791980973 30
1791980978 32
1791980984 32
1791980989 27
1791980994 27
1791980999 27
1791981004 27
1791981009 25
```
</details>

---

