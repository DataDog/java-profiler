---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 17:16:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1794435094 59
1794435099 59
1794435104 59
1794435109 59
1794435114 57
1794435119 57
1794435124 57
1794435129 57
1794435134 57
1794435139 57
1794435144 57
1794435149 57
1794435154 57
1794435159 57
1794435164 57
1794435169 57
1794435174 57
1794435179 57
1794435184 57
1794435189 57
```
</details>

---

