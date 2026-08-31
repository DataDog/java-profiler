---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788139168 88
1788139173 88
1788139178 88
1788139183 88
1788139188 88
1788139193 96
1788139198 96
1788139203 96
1788139208 96
1788139213 96
1788139218 96
1788139223 96
1788139228 96
1788139233 96
1788139238 96
1788139243 96
1788139248 96
1788139253 96
1788139258 96
1788139263 96
```
</details>

---

