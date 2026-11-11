---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 07:14:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 71-96 cores)</summary>

```
1794398956 96
1794398961 96
1794398966 96
1794398971 71
1794398976 71
1794398981 71
1794398986 71
1794398991 71
1794398996 71
1794399001 71
1794399006 71
1794399011 71
1794399016 71
1794399021 71
1794399026 71
1794399031 71
1794399036 71
1794399041 71
1794399046 71
1794399051 71
```
</details>

---

