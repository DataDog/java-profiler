---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 12:53:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1794592160 74
1794592165 74
1794592170 74
1794592175 74
1794592180 74
1794592185 74
1794592190 74
1794592195 74
1794592200 74
1794592205 74
1794592210 74
1794592215 74
1794592220 77
1794592225 77
1794592230 77
1794592235 77
1794592240 77
1794592245 79
1794592250 79
1794592255 79
```
</details>

---

