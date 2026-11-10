---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:19 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 36-71 cores)</summary>

```
1794326098 69
1794326103 69
1794326108 69
1794326113 71
1794326118 71
1794326123 71
1794326128 71
1794326133 71
1794326138 71
1794326144 71
1794326149 38
1794326154 38
1794326159 38
1794326164 38
1794326169 38
1794326174 38
1794326179 38
1794326184 38
1794326189 38
1794326194 38
```
</details>

---

