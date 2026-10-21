---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 05:55:33 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 71-96 cores)</summary>

```
1792576225 96
1792576230 96
1792576235 96
1792576240 96
1792576245 96
1792576250 96
1792576255 94
1792576260 94
1792576265 94
1792576270 94
1792576275 73
1792576280 73
1792576285 73
1792576290 73
1792576295 73
1792576300 73
1792576305 73
1792576310 73
1792576315 73
1792576320 73
```
</details>

---

