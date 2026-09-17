---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:29:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 42-51 cores)</summary>

```
1789680091 42
1789680096 42
1789680101 42
1789680106 42
1789680111 42
1789680116 42
1789680121 42
1789680126 42
1789680131 42
1789680136 42
1789680141 42
1789680146 42
1789680151 42
1789680156 42
1789680161 42
1789680166 42
1789680171 42
1789680176 42
1789680181 42
1789680186 42
```
</details>

---

