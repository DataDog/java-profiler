---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 14:54:04 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 77-94 cores)</summary>

```
1794340094 79
1794340099 79
1794340104 79
1794340110 79
1794340115 79
1794340120 79
1794340125 77
1794340130 77
1794340135 77
1794340140 77
1794340145 77
1794340150 77
1794340155 77
1794340160 77
1794340165 77
1794340170 77
1794340175 77
1794340180 94
1794340185 94
1794340190 94
```
</details>

---

