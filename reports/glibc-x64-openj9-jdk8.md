---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 11:07:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1789743506 12
1789743511 12
1789743516 12
1789743521 12
1789743526 12
1789743531 12
1789743536 12
1789743541 12
1789743546 12
1789743551 12
1789743556 12
1789743561 12
1789743566 12
1789743571 12
1789743576 12
1789743581 12
1789743586 12
1789743591 12
1789743596 12
1789743601 10
```
</details>

---

