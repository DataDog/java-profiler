---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:21:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 83-86 cores)</summary>

```
1794478665 83
1794478670 83
1794478675 83
1794478680 83
1794478685 83
1794478690 83
1794478695 83
1794478700 83
1794478705 83
1794478710 83
1794478715 86
1794478720 86
1794478725 86
1794478730 84
1794478735 84
1794478740 84
1794478745 84
1794478750 84
1794478755 84
1794478760 84
```
</details>

---

