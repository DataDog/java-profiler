---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:33:12 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1789680180 94
1789680185 94
1789680190 94
1789680195 94
1789680200 94
1789680205 96
1789680210 96
1789680215 96
1789680220 96
1789680225 96
1789680230 96
1789680235 96
1789680240 96
1789680245 90
1789680250 90
1789680255 90
1789680260 90
1789680265 90
1789680270 90
1789680275 90
```
</details>

---

