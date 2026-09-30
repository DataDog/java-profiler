---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 06:19:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 19-32 cores)</summary>

```
1790763152 19
1790763157 19
1790763162 19
1790763167 19
1790763172 19
1790763177 19
1790763182 19
1790763187 19
1790763192 30
1790763197 30
1790763202 30
1790763207 30
1790763212 30
1790763217 30
1790763222 30
1790763227 30
1790763232 30
1790763237 30
1790763242 32
1790763247 32
```
</details>

---

