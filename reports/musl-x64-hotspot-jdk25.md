---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-04 10:23:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 13 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 84-96 cores)</summary>

```
1770218173 84
1770218178 84
1770218183 84
1770218188 84
1770218193 84
1770218198 86
1770218203 86
1770218208 86
1770218213 86
1770218218 86
1770218223 86
1770218228 86
1770218233 86
1770218238 86
1770218243 86
1770218248 88
1770218253 88
1770218258 88
1770218263 88
1770218268 88
```
</details>

---

