---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 10:29:18 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 55-63 cores)</summary>

```
1792678987 61
1792678992 61
1792678997 61
1792679002 63
1792679007 63
1792679012 63
1792679017 63
1792679022 63
1792679027 63
1792679032 63
1792679037 63
1792679042 63
1792679047 63
1792679052 63
1792679057 63
1792679062 63
1792679067 63
1792679072 63
1792679077 63
1792679082 63
```
</details>

---

