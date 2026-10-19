---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:04:26 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 66-74 cores)</summary>

```
1792400097 66
1792400102 66
1792400107 66
1792400112 66
1792400117 66
1792400122 68
1792400127 68
1792400132 68
1792400137 68
1792400142 68
1792400147 72
1792400152 72
1792400157 72
1792400162 72
1792400167 74
1792400172 74
1792400177 74
1792400182 74
1792400187 74
1792400192 74
```
</details>

---

