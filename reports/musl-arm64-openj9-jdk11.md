---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:23:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794910608 46
1794910613 46
1794910618 46
1794910623 46
1794910628 46
1794910633 46
1794910638 46
1794910643 46
1794910648 46
1794910653 46
1794910658 46
1794910663 46
1794910668 51
1794910673 51
1794910678 51
1794910683 51
1794910688 51
1794910693 51
1794910698 51
1794910703 51
```
</details>

---

