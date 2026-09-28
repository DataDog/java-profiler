---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 06:45:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 10 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 36-43 cores)</summary>

```
1790592094 43
1790592099 43
1790592104 37
1790592109 37
1790592114 37
1790592119 37
1790592124 37
1790592129 37
1790592134 37
1790592139 37
1790592144 37
1790592149 37
1790592154 36
1790592159 36
1790592164 36
1790592169 36
1790592174 36
1790592179 36
1790592184 36
1790592189 36
```
</details>

---

