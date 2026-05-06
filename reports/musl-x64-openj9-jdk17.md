---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-06 08:41:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1002 |
| Sample Rate | 16.70/sec |
| Health Score | 1044% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 32-37 cores)</summary>

```
1778071091 34
1778071096 34
1778071101 34
1778071106 34
1778071111 34
1778071116 34
1778071121 34
1778071126 34
1778071131 34
1778071136 34
1778071141 34
1778071146 34
1778071151 34
1778071156 37
1778071161 37
1778071166 37
1778071171 37
1778071176 37
1778071181 37
1778071186 37
```
</details>

---

