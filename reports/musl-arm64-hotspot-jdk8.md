---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1791908939 40
1791908944 40
1791908949 40
1791908954 40
1791908959 40
1791908964 48
1791908969 48
1791908974 48
1791908979 48
1791908984 48
1791908989 48
1791908994 48
1791908999 48
1791909004 48
1791909009 48
1791909014 48
1791909019 36
1791909024 36
1791909029 36
1791909034 36
```
</details>

---

