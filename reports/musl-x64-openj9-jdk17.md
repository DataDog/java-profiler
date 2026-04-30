---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:30:48 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1024 |
| Sample Rate | 17.07/sec |
| Health Score | 1067% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 80-92 cores)</summary>

```
1777559059 80
1777559064 80
1777559069 80
1777559074 80
1777559079 80
1777559084 80
1777559089 80
1777559094 80
1777559099 82
1777559104 82
1777559109 82
1777559114 82
1777559119 82
1777559124 82
1777559129 82
1777559134 82
1777559139 82
1777559144 82
1777559149 92
1777559154 92
```
</details>

---

