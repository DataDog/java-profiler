---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 09:51:40 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 12 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1787147069 24
1787147074 24
1787147079 24
1787147084 24
1787147089 44
1787147094 44
1787147099 24
1787147104 24
1787147109 24
1787147114 24
1787147119 24
1787147124 24
1787147129 24
1787147134 24
1787147139 24
1787147144 24
1787147149 24
1787147154 24
1787147159 24
1787147164 24
```
</details>

---

