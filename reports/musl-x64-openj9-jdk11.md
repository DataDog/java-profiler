---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:48:59 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1063 |
| Sample Rate | 17.72/sec |
| Health Score | 1108% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 62-85 cores)</summary>

```
1778093005 64
1778093010 64
1778093015 64
1778093020 64
1778093025 64
1778093030 66
1778093035 66
1778093040 66
1778093045 66
1778093050 66
1778093055 66
1778093060 62
1778093065 62
1778093070 85
1778093075 85
1778093080 85
1778093085 66
1778093090 66
1778093095 66
1778093100 66
```
</details>

---

