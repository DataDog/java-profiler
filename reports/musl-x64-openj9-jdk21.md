---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 04:34:48 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1787128126 32
1787128131 32
1787128136 32
1787128141 32
1787128146 32
1787128151 32
1787128156 32
1787128161 32
1787128166 30
1787128171 30
1787128176 30
1787128181 30
1787128186 30
1787128191 30
1787128196 30
1787128201 30
1787128206 30
1787128211 30
1787128216 30
1787128221 30
```
</details>

---

