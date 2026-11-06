---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 09:29:17 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 60-70 cores)</summary>

```
1793975154 60
1793975159 60
1793975164 60
1793975169 60
1793975174 62
1793975179 62
1793975184 62
1793975189 70
1793975194 70
1793975199 70
1793975204 70
1793975209 70
1793975214 70
1793975219 68
1793975224 68
1793975229 68
1793975234 68
1793975239 68
1793975244 68
1793975249 68
```
</details>

---

