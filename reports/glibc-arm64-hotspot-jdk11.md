---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:39:38 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1792532086 36
1792532091 36
1792532096 36
1792532101 36
1792532106 36
1792532111 36
1792532116 36
1792532121 36
1792532126 48
1792532131 48
1792532136 48
1792532141 48
1792532146 48
1792532151 48
1792532156 48
1792532161 48
1792532166 48
1792532172 48
1792532177 48
1792532182 48
```
</details>

---

