---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 10:08:05 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 24-29 cores)</summary>

```
1792504976 27
1792504981 27
1792504986 27
1792504991 27
1792504996 27
1792505001 27
1792505006 27
1792505011 25
1792505016 25
1792505021 27
1792505026 27
1792505031 24
1792505036 24
1792505041 24
1792505046 24
1792505051 24
1792505057 24
1792505062 24
1792505067 24
1792505072 29
```
</details>

---

