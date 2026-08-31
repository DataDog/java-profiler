---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:26:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 63-83 cores)</summary>

```
1788139153 83
1788139158 83
1788139163 83
1788139168 83
1788139173 83
1788139178 83
1788139183 83
1788139188 83
1788139193 83
1788139198 83
1788139203 83
1788139208 83
1788139213 83
1788139218 83
1788139223 83
1788139228 83
1788139233 63
1788139238 63
1788139243 63
1788139248 63
```
</details>

---

