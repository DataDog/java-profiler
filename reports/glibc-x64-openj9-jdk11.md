---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:50:41 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 58-66 cores)</summary>

```
1790855140 66
1790855145 66
1790855150 66
1790855155 64
1790855160 64
1790855165 64
1790855170 64
1790855175 66
1790855180 66
1790855185 66
1790855190 66
1790855195 66
1790855200 66
1790855205 63
1790855210 63
1790855215 63
1790855220 63
1790855225 63
1790855230 63
1790855235 63
```
</details>

---

