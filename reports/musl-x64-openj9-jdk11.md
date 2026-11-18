---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:05 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (7 unique values: 38-47 cores)</summary>

```
1794999171 41
1794999176 41
1794999181 43
1794999186 43
1794999191 45
1794999196 45
1794999201 42
1794999206 42
1794999211 40
1794999216 40
1794999221 38
1794999226 38
1794999231 38
1794999236 38
1794999241 38
1794999246 38
1794999251 38
1794999256 47
1794999261 47
1794999266 47
```
</details>

---

