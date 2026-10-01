---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:50:45 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 66-91 cores)</summary>

```
1790855127 66
1790855132 68
1790855137 68
1790855142 66
1790855147 66
1790855152 66
1790855158 66
1790855163 66
1790855168 66
1790855173 91
1790855178 91
1790855183 91
1790855188 79
1790855193 79
1790855198 79
1790855203 79
1790855208 79
1790855213 79
1790855218 79
1790855223 79
```
</details>

---

