---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1795196145 66
1795196150 66
1795196155 66
1795196160 70
1795196165 70
1795196170 70
1795196175 70
1795196180 70
1795196185 70
1795196190 70
1795196195 70
1795196200 70
1795196205 68
1795196210 68
1795196215 68
1795196220 68
1795196225 68
1795196230 68
1795196235 68
1795196240 68
```
</details>

---

