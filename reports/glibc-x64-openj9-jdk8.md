---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 17:33:13 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1789680165 93
1789680170 93
1789680175 95
1789680180 95
1789680185 95
1789680190 95
1789680195 96
1789680200 96
1789680205 96
1789680210 88
1789680215 88
1789680220 88
1789680225 88
1789680230 88
1789680235 88
1789680240 88
1789680245 88
1789680250 88
1789680255 88
1789680260 88
```
</details>

---

