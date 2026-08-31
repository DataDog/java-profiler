---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788139153 64
1788139158 64
1788139163 64
1788139168 64
1788139173 64
1788139178 64
1788139183 64
1788139188 64
1788139193 64
1788139198 64
1788139203 64
1788139208 64
1788139213 64
1788139218 64
1788139223 64
1788139228 64
1788139233 64
1788139238 64
1788139243 64
1788139248 64
```
</details>

---

