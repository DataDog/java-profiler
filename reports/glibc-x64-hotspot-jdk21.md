---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 07:51:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794401195 32
1794401200 32
1794401205 32
1794401210 32
1794401215 32
1794401220 32
1794401225 32
1794401230 32
1794401235 32
1794401240 32
1794401245 32
1794401250 30
1794401255 30
1794401260 30
1794401265 30
1794401270 30
1794401275 30
1794401280 30
1794401285 30
1794401290 30
```
</details>

---

