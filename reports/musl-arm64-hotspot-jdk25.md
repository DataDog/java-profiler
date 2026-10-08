---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:54:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 47-53 cores)</summary>

```
1791470929 48
1791470934 48
1791470939 48
1791470944 48
1791470949 48
1791470954 48
1791470959 48
1791470964 48
1791470969 48
1791470974 48
1791470979 48
1791470984 53
1791470989 53
1791470994 47
1791470999 47
1791471004 47
1791471009 47
1791471014 47
1791471019 47
1791471024 47
```
</details>

---

