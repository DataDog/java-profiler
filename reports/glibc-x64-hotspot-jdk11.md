---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:21:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1788139001 85
1788139006 85
1788139011 85
1788139016 85
1788139021 85
1788139026 87
1788139031 87
1788139036 87
1788139041 87
1788139046 96
1788139051 96
1788139056 87
1788139061 87
1788139066 87
1788139071 87
1788139076 87
1788139081 87
1788139086 87
1788139091 87
1788139096 87
```
</details>

---

