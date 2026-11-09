---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:22:28 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (3 unique values: 75-89 cores)</summary>

```
1794259062 75
1794259067 75
1794259072 75
1794259077 75
1794259082 75
1794259087 75
1794259092 75
1794259097 75
1794259102 75
1794259107 75
1794259112 75
1794259117 75
1794259122 75
1794259127 87
1794259132 87
1794259137 87
1794259142 87
1794259147 89
1794259152 89
1794259157 89
```
</details>

---

