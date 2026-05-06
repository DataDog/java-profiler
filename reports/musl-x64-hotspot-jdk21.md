---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:48:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 65-78 cores)</summary>

```
1778093010 72
1778093015 72
1778093020 72
1778093025 72
1778093030 72
1778093035 72
1778093040 67
1778093045 67
1778093050 69
1778093056 69
1778093061 69
1778093066 69
1778093071 69
1778093076 69
1778093081 69
1778093086 69
1778093091 69
1778093096 69
1778093101 67
1778093106 67
```
</details>

---

