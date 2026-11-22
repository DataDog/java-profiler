---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 17:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 42-68 cores)</summary>

```
1795386126 68
1795386131 68
1795386136 68
1795386141 68
1795386146 68
1795386151 68
1795386156 68
1795386161 68
1795386166 68
1795386171 68
1795386176 68
1795386181 68
1795386186 68
1795386191 68
1795386196 68
1795386201 68
1795386206 68
1795386211 68
1795386216 68
1795386221 42
```
</details>

---

