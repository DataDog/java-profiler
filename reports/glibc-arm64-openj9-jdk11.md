---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:15:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777324058 64
1777324063 64
1777324068 64
1777324073 64
1777324078 64
1777324083 64
1777324088 64
1777324093 64
1777324098 64
1777324103 64
1777324108 64
1777324113 64
1777324118 64
1777324123 64
1777324128 64
1777324133 64
1777324138 64
1777324143 64
1777324148 64
1777324153 64
```
</details>

---

