---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:29:29 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 7-24 cores)</summary>

```
1789680155 15
1789680160 15
1789680165 15
1789680170 15
1789680175 15
1789680180 15
1789680185 15
1789680190 15
1789680195 15
1789680200 15
1789680205 7
1789680210 7
1789680215 24
1789680220 24
1789680225 24
1789680230 24
1789680235 24
1789680240 24
1789680245 9
1789680250 9
```
</details>

---

