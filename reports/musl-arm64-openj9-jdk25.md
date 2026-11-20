---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:51:37 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795171552 50
1795171557 50
1795171563 50
1795171568 50
1795171573 50
1795171578 50
1795171583 50
1795171588 50
1795171593 50
1795171598 50
1795171603 50
1795171608 50
1795171613 50
1795171618 50
1795171623 50
1795171628 50
1795171633 50
1795171638 50
1795171643 50
1795171648 50
```
</details>

---

