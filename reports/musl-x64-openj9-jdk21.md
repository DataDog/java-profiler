---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:38:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1793367156 87
1793367161 87
1793367166 89
1793367171 89
1793367176 89
1793367181 89
1793367186 89
1793367191 89
1793367196 89
1793367201 89
1793367206 89
1793367211 89
1793367216 89
1793367221 89
1793367226 89
1793367231 89
1793367236 89
1793367241 89
1793367246 86
1793367251 86
```
</details>

---

