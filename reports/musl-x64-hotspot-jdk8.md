---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 07:20:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 58-67 cores)</summary>

```
1795436124 58
1795436129 58
1795436134 58
1795436139 67
1795436144 67
1795436149 67
1795436154 67
1795436159 67
1795436164 67
1795436169 67
1795436174 67
1795436179 62
1795436184 62
1795436189 62
1795436194 62
1795436199 62
1795436204 62
1795436209 62
1795436214 62
1795436219 62
```
</details>

---

