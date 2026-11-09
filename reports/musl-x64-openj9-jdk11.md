---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 09:27:57 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1794234141 49
1794234146 49
1794234151 49
1794234156 49
1794234161 49
1794234166 49
1794234171 49
1794234176 49
1794234181 47
1794234186 47
1794234191 47
1794234196 47
1794234201 47
1794234207 47
1794234212 47
1794234217 47
1794234222 47
1794234227 47
1794234232 47
1794234237 47
```
</details>

---

