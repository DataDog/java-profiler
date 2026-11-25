---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 15 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (2 unique values: 43-60 cores)</summary>

```
1795626813 43
1795626818 43
1795626823 43
1795626828 43
1795626833 43
1795626838 43
1795626843 43
1795626848 43
1795626853 43
1795626858 43
1795626864 43
1795626869 43
1795626874 43
1795626879 43
1795626884 43
1795626889 60
1795626894 60
1795626899 60
1795626904 60
1795626909 60
```
</details>

---

