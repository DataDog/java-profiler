---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:38:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1793367153 59
1793367159 59
1793367164 59
1793367169 59
1793367174 59
1793367179 59
1793367184 59
1793367189 59
1793367194 59
1793367199 59
1793367204 59
1793367209 59
1793367214 59
1793367219 59
1793367224 59
1793367229 59
1793367234 59
1793367239 59
1793367244 59
1793367249 54
```
</details>

---

