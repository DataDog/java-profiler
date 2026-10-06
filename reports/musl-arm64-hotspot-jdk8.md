---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 11:23:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1791299928 51
1791299933 51
1791299938 51
1791299943 51
1791299948 51
1791299953 51
1791299958 51
1791299963 51
1791299968 51
1791299973 51
1791299978 51
1791299984 51
1791299989 51
1791299994 51
1791299999 51
1791300004 31
1791300009 31
1791300014 31
1791300019 31
1791300024 31
```
</details>

---

