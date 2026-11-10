---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:40:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794324923 29
1794324928 29
1794324933 29
1794324938 29
1794324943 29
1794324948 29
1794324953 29
1794324958 27
1794324963 27
1794324968 27
1794324973 27
1794324978 27
1794324983 27
1794324988 27
1794324993 27
1794324998 27
1794325003 27
1794325008 27
1794325013 27
1794325018 29
```
</details>

---

