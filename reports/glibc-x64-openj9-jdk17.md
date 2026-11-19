---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:36:49 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1795113108 81
1795113113 81
1795113118 81
1795113123 81
1795113128 81
1795113133 81
1795113138 81
1795113143 81
1795113148 81
1795113153 81
1795113158 81
1795113163 81
1795113168 81
1795113173 83
1795113178 83
1795113183 83
1795113188 83
1795113193 83
1795113198 83
1795113203 83
```
</details>

---

