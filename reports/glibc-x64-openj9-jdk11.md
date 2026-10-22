---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 17:27:05 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1792704088 28
1792704093 28
1792704098 30
1792704103 30
1792704108 30
1792704113 30
1792704118 30
1792704123 30
1792704128 30
1792704133 30
1792704138 30
1792704143 30
1792704148 30
1792704153 30
1792704158 30
1792704163 30
1792704168 30
1792704173 30
1792704178 30
1792704183 30
```
</details>

---

