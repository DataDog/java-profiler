---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:47:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1794408139 58
1794408144 58
1794408149 58
1794408154 58
1794408159 58
1794408164 58
1794408169 56
1794408174 56
1794408179 56
1794408184 56
1794408189 56
1794408194 56
1794408199 56
1794408204 56
1794408209 56
1794408214 56
1794408219 56
1794408224 56
1794408229 56
1794408235 56
```
</details>

---

