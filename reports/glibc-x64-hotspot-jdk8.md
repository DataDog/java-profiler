---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:33:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795011985 47
1795011990 47
1795011995 47
1795012000 47
1795012006 47
1795012011 47
1795012016 47
1795012021 47
1795012026 47
1795012031 47
1795012036 47
1795012041 47
1795012046 47
1795012051 47
1795012056 42
1795012061 42
1795012066 42
1795012071 42
1795012076 42
1795012081 42
```
</details>

---

