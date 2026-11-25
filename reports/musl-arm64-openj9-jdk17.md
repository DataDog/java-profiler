---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 03:20:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795594578 64
1795594583 64
1795594588 64
1795594593 64
1795594598 64
1795594603 64
1795594608 64
1795594613 64
1795594618 64
1795594623 64
1795594628 64
1795594633 64
1795594638 64
1795594643 64
1795594648 64
1795594653 64
1795594658 64
1795594663 64
1795594668 64
1795594673 64
```
</details>

---

