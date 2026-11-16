---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:41:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794793102 48
1794793107 48
1794793112 48
1794793117 48
1794793122 48
1794793127 48
1794793132 48
1794793137 48
1794793142 48
1794793147 48
1794793152 48
1794793157 48
1794793162 48
1794793167 48
1794793172 48
1794793177 48
1794793182 48
1794793187 48
1794793192 48
1794793197 48
```
</details>

---

