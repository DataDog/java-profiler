---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 11:01:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1794326137 64
1794326142 66
1794326147 66
1794326152 66
1794326157 66
1794326162 66
1794326167 66
1794326172 66
1794326177 68
1794326182 68
1794326187 68
1794326192 68
1794326197 68
1794326202 68
1794326207 68
1794326212 68
1794326217 68
1794326222 68
1794326227 66
1794326232 66
```
</details>

---

