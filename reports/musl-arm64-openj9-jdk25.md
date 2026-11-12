---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:33:53 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 11 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1794508056 47
1794508061 47
1794508066 47
1794508071 47
1794508076 47
1794508081 47
1794508086 47
1794508091 47
1794508096 47
1794508101 48
1794508106 48
1794508111 48
1794508116 48
1794508121 48
1794508126 48
1794508131 48
1794508136 48
1794508141 48
1794508146 48
1794508152 48
```
</details>

---

