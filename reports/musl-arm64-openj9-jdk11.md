---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:49:17 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 11 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 41-45 cores)</summary>

```
1794501690 42
1794501695 42
1794501700 42
1794501705 42
1794501710 42
1794501715 44
1794501720 44
1794501725 44
1794501730 44
1794501735 44
1794501740 44
1794501745 45
1794501750 45
1794501755 43
1794501760 43
1794501765 43
1794501770 43
1794501775 43
1794501780 41
1794501785 41
```
</details>

---

