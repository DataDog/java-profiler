---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 52-74 cores)</summary>

```
1794998162 52
1794998167 52
1794998172 52
1794998177 52
1794998182 52
1794998187 52
1794998192 52
1794998197 52
1794998202 52
1794998207 52
1794998212 54
1794998217 54
1794998222 54
1794998227 74
1794998232 74
1794998237 65
1794998242 65
1794998247 67
1794998252 67
1794998257 67
```
</details>

---

