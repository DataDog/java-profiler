---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:43:44 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 54-64 cores)</summary>

```
1794998137 54
1794998142 54
1794998147 54
1794998152 54
1794998157 54
1794998162 54
1794998167 64
1794998172 64
1794998177 64
1794998182 64
1794998187 64
1794998192 64
1794998197 64
1794998202 64
1794998207 64
1794998212 59
1794998217 59
1794998222 61
1794998227 61
1794998232 59
```
</details>

---

