---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:02:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1794427056 82
1794427061 82
1794427066 84
1794427071 84
1794427076 84
1794427081 84
1794427086 84
1794427091 84
1794427096 84
1794427101 84
1794427106 84
1794427111 84
1794427116 84
1794427121 84
1794427126 84
1794427131 84
1794427136 84
1794427141 84
1794427146 84
1794427151 84
```
</details>

---

