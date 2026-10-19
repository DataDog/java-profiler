---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 21:28:18 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792372991 48
1792372996 48
1792373001 48
1792373006 48
1792373011 48
1792373016 48
1792373021 43
1792373026 43
1792373031 43
1792373036 43
1792373041 43
1792373046 43
1792373051 43
1792373056 43
1792373061 48
1792373066 48
1792373071 48
1792373076 48
1792373081 48
1792373086 48
```
</details>

---

