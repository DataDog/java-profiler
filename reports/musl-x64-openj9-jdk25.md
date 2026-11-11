---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:07:54 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 77-96 cores)</summary>

```
1794395005 96
1794395010 96
1794395015 77
1794395020 77
1794395025 77
1794395030 77
1794395035 77
1794395040 77
1794395045 77
1794395050 77
1794395055 77
1794395060 77
1794395065 77
1794395070 77
1794395075 77
1794395080 77
1794395085 77
1794395090 77
1794395095 77
1794395100 77
```
</details>

---

