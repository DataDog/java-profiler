---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:28:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792373041 32
1792373046 32
1792373051 32
1792373056 32
1792373061 32
1792373066 32
1792373071 32
1792373076 32
1792373081 32
1792373086 32
1792373091 32
1792373096 32
1792373101 32
1792373106 32
1792373111 32
1792373116 32
1792373121 32
1792373126 32
1792373131 32
1792373136 32
```
</details>

---

