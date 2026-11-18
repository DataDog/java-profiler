---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:52:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 63-78 cores)</summary>

```
1795013148 78
1795013153 78
1795013158 78
1795013163 78
1795013168 78
1795013173 78
1795013178 78
1795013183 78
1795013188 78
1795013193 78
1795013198 78
1795013203 78
1795013208 78
1795013213 78
1795013218 78
1795013223 78
1795013228 69
1795013233 69
1795013238 69
1795013243 69
```
</details>

---

