---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-07 10:01:23 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 13 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794063466 43
1794063471 43
1794063476 43
1794063481 43
1794063486 43
1794063491 43
1794063496 43
1794063501 43
1794063506 43
1794063511 43
1794063516 43
1794063521 43
1794063526 38
1794063531 38
1794063536 38
1794063541 38
1794063546 38
1794063551 38
1794063556 38
1794063561 38
```
</details>

---

