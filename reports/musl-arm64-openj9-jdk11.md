---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 15:19:46 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794341675 46
1794341680 46
1794341685 46
1794341690 46
1794341695 46
1794341700 48
1794341705 48
1794341710 48
1794341715 48
1794341720 48
1794341725 48
1794341730 48
1794341735 48
1794341740 48
1794341745 48
1794341750 48
1794341755 48
1794341760 48
1794341765 48
1794341770 48
```
</details>

---

