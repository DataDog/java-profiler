---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 12:51:46 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770140758 32
1770140763 32
1770140768 32
1770140773 32
1770140778 32
1770140783 32
1770140788 32
1770140793 32
1770140798 32
1770140803 32
1770140808 32
1770140813 32
1770140818 32
1770140823 32
1770140828 32
1770140833 32
1770140838 32
1770140843 32
1770140848 32
1770140853 32
```
</details>

---

