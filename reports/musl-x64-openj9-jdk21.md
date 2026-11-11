---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:47:16 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 73-76 cores)</summary>

```
1794408129 76
1794408134 76
1794408139 76
1794408144 76
1794408149 76
1794408154 76
1794408159 76
1794408164 76
1794408169 76
1794408174 76
1794408179 76
1794408184 76
1794408189 76
1794408194 76
1794408199 76
1794408204 76
1794408209 73
1794408214 73
1794408219 73
1794408224 73
```
</details>

---

