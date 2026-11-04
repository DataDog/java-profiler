---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 14:11:23 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 52-62 cores)</summary>

```
1793819185 54
1793819190 54
1793819195 54
1793819200 52
1793819205 52
1793819210 52
1793819215 52
1793819220 52
1793819225 52
1793819230 52
1793819235 52
1793819240 57
1793819245 57
1793819250 62
1793819255 62
1793819260 62
1793819265 62
1793819270 62
1793819275 62
1793819280 62
```
</details>

---

