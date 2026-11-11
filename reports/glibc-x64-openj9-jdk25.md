---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 07:51:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1794401180 52
1794401185 52
1794401190 54
1794401195 54
1794401200 54
1794401205 54
1794401210 54
1794401215 54
1794401220 54
1794401225 54
1794401230 54
1794401235 54
1794401240 54
1794401245 54
1794401250 54
1794401255 54
1794401260 52
1794401265 52
1794401270 52
1794401275 52
```
</details>

---

