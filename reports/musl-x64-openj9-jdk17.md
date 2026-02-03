---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 09:53:15 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (6 unique values: 33-49 cores)</summary>

```
1770130089 33
1770130094 33
1770130099 38
1770130104 38
1770130109 36
1770130114 36
1770130119 36
1770130124 36
1770130129 36
1770130134 41
1770130139 41
1770130144 49
1770130149 49
1770130154 49
1770130159 49
1770130164 49
1770130169 49
1770130174 49
1770130179 49
1770130184 49
```
</details>

---

