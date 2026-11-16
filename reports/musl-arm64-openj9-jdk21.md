---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:44:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1794843598 47
1794843603 47
1794843608 47
1794843613 47
1794843618 47
1794843623 47
1794843628 45
1794843633 45
1794843638 45
1794843643 45
1794843648 45
1794843653 45
1794843658 45
1794843663 45
1794843668 45
1794843673 45
1794843678 45
1794843683 45
1794843688 45
1794843693 45
```
</details>

---

