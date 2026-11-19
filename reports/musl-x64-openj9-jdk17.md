---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:18:02 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (7 unique values: 40-87 cores)</summary>

```
1795083181 40
1795083186 40
1795083191 40
1795083196 40
1795083201 40
1795083206 40
1795083211 40
1795083216 40
1795083221 51
1795083226 51
1795083231 51
1795083236 51
1795083241 51
1795083246 51
1795083251 51
1795083256 51
1795083261 53
1795083266 53
1795083271 53
1795083276 62
```
</details>

---

