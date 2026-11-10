---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 00:08:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794287001 51
1794287006 49
1794287011 49
1794287016 49
1794287021 49
1794287026 49
1794287031 49
1794287036 49
1794287041 51
1794287046 51
1794287051 51
1794287056 51
1794287061 51
1794287066 51
1794287071 51
1794287076 51
1794287081 51
1794287086 51
1794287091 51
1794287096 51
```
</details>

---

