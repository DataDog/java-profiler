---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (5 unique values: 72-79 cores)</summary>

```
1790763133 79
1790763138 79
1790763143 79
1790763148 79
1790763153 79
1790763158 79
1790763163 79
1790763168 79
1790763173 79
1790763178 77
1790763183 77
1790763188 77
1790763193 77
1790763198 75
1790763203 75
1790763208 75
1790763213 72
1790763218 72
1790763223 72
1790763228 74
```
</details>

---

