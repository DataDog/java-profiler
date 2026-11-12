---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:47:39 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (6 unique values: 62-77 cores)</summary>

```
1794480176 62
1794480181 62
1794480186 62
1794480191 62
1794480196 62
1794480201 62
1794480206 65
1794480211 65
1794480216 63
1794480221 63
1794480226 63
1794480231 63
1794480237 66
1794480242 66
1794480247 66
1794480252 66
1794480257 66
1794480262 66
1794480267 66
1794480272 75
```
</details>

---

