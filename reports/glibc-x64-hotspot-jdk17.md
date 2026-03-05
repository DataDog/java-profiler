---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 16-23 cores)</summary>

```
1772735048 16
1772735053 16
1772735058 16
1772735063 16
1772735068 16
1772735073 16
1772735078 16
1772735083 16
1772735088 19
1772735093 19
1772735098 19
1772735103 19
1772735108 19
1772735113 19
1772735118 19
1772735123 19
1772735128 19
1772735133 19
1772735138 19
1772735143 19
```
</details>

---

