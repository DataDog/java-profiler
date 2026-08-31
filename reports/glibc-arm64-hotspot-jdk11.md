---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:21:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 30-40 cores)</summary>

```
1788139006 30
1788139011 30
1788139016 30
1788139021 30
1788139026 30
1788139031 35
1788139036 35
1788139041 40
1788139046 40
1788139051 40
1788139056 40
1788139061 40
1788139066 40
1788139071 40
1788139076 40
1788139081 40
1788139086 40
1788139091 40
1788139096 40
1788139101 40
```
</details>

---

