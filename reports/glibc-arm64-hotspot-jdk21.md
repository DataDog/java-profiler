---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 07:20:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 44-48 cores)</summary>

```
1795436173 44
1795436178 44
1795436183 44
1795436188 44
1795436193 44
1795436198 44
1795436203 44
1795436208 44
1795436213 44
1795436218 44
1795436223 46
1795436228 46
1795436233 48
1795436238 48
1795436243 47
1795436248 47
1795436253 47
1795436258 47
1795436263 47
1795436268 47
```
</details>

---

