---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:23:44 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 7 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788139051 43
1788139056 43
1788139061 48
1788139066 48
1788139071 48
1788139076 48
1788139081 48
1788139086 48
1788139091 48
1788139096 48
1788139101 48
1788139106 48
1788139111 48
1788139116 48
1788139121 48
1788139126 48
1788139131 48
1788139136 43
1788139141 43
1788139146 43
```
</details>

---

