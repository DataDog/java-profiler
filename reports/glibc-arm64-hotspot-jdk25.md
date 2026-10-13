---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 15 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1791909003 39
1791909008 39
1791909013 39
1791909018 39
1791909023 34
1791909028 34
1791909033 34
1791909038 34
1791909043 34
1791909048 34
1791909053 34
1791909058 34
1791909063 34
1791909068 34
1791909073 34
1791909078 34
1791909083 34
1791909088 34
1791909093 34
1791909098 34
```
</details>

---

