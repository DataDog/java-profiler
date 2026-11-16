---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:41:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794793091 32
1794793096 32
1794793101 32
1794793106 32
1794793111 32
1794793116 32
1794793121 32
1794793126 32
1794793131 32
1794793136 32
1794793141 32
1794793146 32
1794793151 32
1794793156 32
1794793161 32
1794793166 32
1794793171 32
1794793176 32
1794793181 32
1794793186 32
```
</details>

---

