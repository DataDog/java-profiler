---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 06:45:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 11 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1790592059 43
1790592064 43
1790592069 43
1790592074 43
1790592079 43
1790592084 43
1790592089 43
1790592094 43
1790592099 43
1790592104 43
1790592109 41
1790592114 41
1790592119 41
1790592124 41
1790592129 41
1790592134 41
1790592139 41
1790592144 41
1790592149 41
1790592154 41
```
</details>

---

