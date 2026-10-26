---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 16:16:45 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 84-91 cores)</summary>

```
1793045192 91
1793045197 91
1793045202 91
1793045207 91
1793045212 91
1793045217 89
1793045222 89
1793045227 89
1793045232 84
1793045237 84
1793045242 84
1793045247 84
1793045252 84
1793045257 84
1793045262 84
1793045267 84
1793045272 84
1793045277 84
1793045282 86
1793045287 86
```
</details>

---

