---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 51-54 cores)</summary>

```
1795113108 51
1795113113 51
1795113118 51
1795113123 54
1795113128 54
1795113133 52
1795113138 52
1795113143 52
1795113148 52
1795113153 52
1795113158 52
1795113163 52
1795113168 52
1795113173 52
1795113178 54
1795113183 54
1795113188 54
1795113193 54
1795113198 54
1795113203 54
```
</details>

---

