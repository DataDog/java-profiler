---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:52:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1795013133 30
1795013138 30
1795013143 30
1795013148 30
1795013153 30
1795013158 30
1795013163 30
1795013168 30
1795013173 30
1795013178 30
1795013183 30
1795013188 30
1795013193 30
1795013198 30
1795013203 30
1795013208 32
1795013213 32
1795013218 30
1795013223 30
1795013228 30
```
</details>

---

